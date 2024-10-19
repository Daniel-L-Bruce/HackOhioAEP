#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <set>
#include <string>

#include "csvstream.hpp"

using namespace std;

class Classifier {
 private:
  // private data members should keep track of the classifier parameters
  // learned from training data
  // total number of posts in the entire training set
  int num_training_posts = 0;
  // the number of unique words in the entire training set
  int num_unique_words = 0;
  // for each word w, the number of posts in the entire training set that
  // contain w
  map<string, int> num_posts_words;
  // for each label C, the number of posts with that label
  map<string, int> num_posts_label;
  // for each label C and word w, the number of posts with label C that contain
  // w (map of pairs - can also use map of maps, up to u)
  map<pair<string, string>, int> num_posts_LW;

 public:
  // public member functions should provide an interface that allows you to
  // train the classifier and make predictions for new piazza posts

  // unique words implementation from spec
  set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
      words.insert(word);
    }
    return words;
  }

  // First, your application should read posts from a file (e.g.
  // train_small.csv) and use them to train the classifier. After training, your
  // classifier abstraction should store the information mentioned in the
  // Training section.
  void train(csvstream &csvin, bool debug);

  // Second, your classifier should be able to compute the log-probability score
  // of a post (i.e. a collection of words) given a particular label. To predict
  // a label for a new post, it should choose the label that gives the highest
  // log-probability score. See the Prediction section.

  double log_prior_prob(const string &label) {
    int num_posts_with_label = num_posts_label[label];

    // log=prior-probability formula of label C to find how common it is
    return log(static_cast<double>(num_posts_with_label) / num_training_posts);
  }

  double log_likelihood(const string &label, const string &word) {
    int num_posts_with_label_word = num_posts_LW[{label, word}];
    int num_posts_with_word = num_posts_words[word];
    int num_posts_with_label = num_posts_label[label];

    // word w does not occur anywhere at all in the training set
    if (num_posts_with_word == 0) {
      return log(1.0 / static_cast<double>(num_training_posts));

      // word w does not occur in posts labeled C but does occur in the training
      // data overall
    } else if (num_posts_with_label_word == 0) {
      return log(static_cast<double>(num_posts_with_word) /
                 static_cast<double>(num_training_posts));

      // regular log-likehood formula to measure how likely it is to see word w
      // in posts with label C
    } else {
      return log(static_cast<double>(num_posts_with_label_word) /
                 static_cast<double>(num_posts_with_label));
    }
  }

  // Third and last, read posts from a file (e.g. test_small.csv) to use as
  // testing data. For each post, predict a label using your classifier.
  void test(csvstream &csvin) {
    cout << "test data:" << endl;

    // initialize "tag" and "content" columns with map "row"
    map<string, string> row;
    set<string> words;
    string label;
    string predicted_label;

    // intialize performance variables for accuracy counter of prediction
    int correct_pred = 0;
    int total_pred = 0;
    double max_log_prob = -numeric_limits<double>::infinity();
    double log_prob = 0;

    // read posts from test csv file to use as testing data
    while (csvin >> row) {
      words = unique_words(row["content"]);
      max_log_prob = -numeric_limits<double>::infinity();
      // calculate log-prior probability of each label
      for (auto &itr1 : num_posts_label) {
        label = itr1.first;
        log_prob = log_prior_prob(label);

        // calculate the log-likelihood of each word in the content
        for (auto &word : words) {
          log_prob += log_likelihood(label, word);
        }

        // predict label based on highest score
        if (log_prob > max_log_prob) {
          max_log_prob = log_prob;
          predicted_label = label;
        }
      }


      // increment correct prediction counter if predicted label is correct
      if (predicted_label == row["tag"]){
        correct_pred++;
      }

      // print information about the test data and predictions
      cout << "  correct = " << row["tag"]
           << ", predicted = " << predicted_label
           << ", log-probability score = " << max_log_prob << endl;
      cout << "  content = " << row["content"] << endl;
      cout << endl;

      // increment total prediction counter for every testing post
      total_pred++;
    }

    // print number of correct predictions and total number of test posts
    cout << "performance: " << correct_pred << " / " << total_pred
         << " posts predicted correctly" << endl;

  }  // end of test()
};   // end of class Classifer

int main(int argc, char *argv[]) {
  cout.precision(3);
  bool debug = false;
  // Error checking: must be 3 or 4 arguments
  if (argc != 3 && argc != 4) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  }

  // If 4 arguments, must be "--debug"
  if (argc == 4) {
    if (strcmp(argv[3], "--debug ") || strcmp(argv[3], "--debug")) {
      debug = true;
    }
    else {
      cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
      return 1;
    }
  }
  // file(s) couldn't be opened and appropriate message and non-zero value is
  // returned

  Classifier *trainer = new Classifier;

  string train_filename = argv[1];
  string test_filename = argv[2];
  csvstream csvin_train(train_filename);
  csvstream csvin_test(test_filename);

  trainer->train(csvin_train,debug);
  trainer->test(csvin_test);

  delete trainer;
}

void Classifier::train(csvstream &csvin, bool debug) {
  // Variable declarations
  map<string, string> row;
  set<string> vocab;
  set<string> words;
  string temp;

  if(debug == true) {
  cout<<"training data:"<<endl;
  }
  // Read through csv file
  while (csvin >> row) {
    // Increment number of training posts
    ++num_training_posts;
    // Get unique words from row content
    words = unique_words(row["content"]);
    // Insert them into the vocab set
    vocab.insert(words.begin(), words.end());
    // Iterate over vocab words
    for (auto const &vocab_w : words) {
      //Increment
      num_posts_words[vocab_w]++;
      num_posts_LW[{row["tag"], vocab_w}]++;
    }
    // increment the number of training posts with label C
    num_posts_label[row["tag"]]++;
    // debug output
    if(debug == true) {
      cout<<"  "<<"label = "<<row["tag"]<<", "
      <<"content = "<<row["content"]<<endl;
    }
  }
  // print number of training posts
  cout << "trained on " << num_training_posts << " examples" << endl;
  // debug output
  if(debug == true) {
    cout<<"vocabulary size = "<<vocab.size()<<endl<<endl
    <<"classes:"<<endl;
    for(auto const &itr : num_posts_label) {
      cout<<"  "<<itr.first<<", "<<itr.second<<" examples, "
      <<"log-prior = "<<log_prior_prob(itr.first)<<endl;
    }
    cout<<"classifier parameters:"<<endl;
    for(auto const &itr2 : num_posts_LW) {
      cout<<"  "<<itr2.first.first<<":"<<itr2.first.second
      <<", count = "<<itr2.second<<", log-likelihood = "
      <<log_likelihood(itr2.first.first,itr2.first.second)<<endl;
    }
    cout<<endl;
  }
  else {
    cout<<endl;
  }
}