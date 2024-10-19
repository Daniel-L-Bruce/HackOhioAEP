#include 

using namespace std;

/* 
1. Was high energy present?
    -Table of icons in appendix 2
    -When energy suprases the 500 ft-lb threshhold
    -Multiple sources must be considered individually
    -Generally, these are:
        -Suspended Load
        -Mobile Equipment
        -Traffic with Workers on foot (Happens when vehicle departs designated path within 6 feet of a worker)
        -Heavy Rotating Equipment
        -Steam
        -Explosion
        -Electrical Contact with source greater than or equal to 50 Volts
        -High Dose of Toxic Chemical/Radiation
        -Fall >= 4 feet
        -When in vehicle going >= 300 mph
        -Temperatures >= 150 F
        -Fire with sustained fuel source
        -Excavation or Trench >= 5 feet deep
        -Arc Flash
        -Tools, materials, or equipment which satisfies Height x Weight >= 500 or Speed x Weight >= 500
2. Did a high-energy incident occur?
    -Equation is as follows:
        HIGH ENERGY + ENERGY RELEASE + CONTACT/PROXIMITY = HIGH-ENERGY INCIDENT
    -Contact: When high energy is transmitted to the human body
    -Proximity:
        -When within 6 feet of a worker
        -Any energy source when it is in a confined space or a worker can not leave
3. Was a serious injury sustained?
    -Defined by appendix 7:
        -Fatalities
        -Amputations
        -Cerebral Hemorrhages
        -Concussions resulting in loss of conssciousness and/or symptoms lasting more than 24 hours
        -Injury or trauma to internal organs; relatively short-term events not long term things
        -Bone Fractures considering:
            -Include finger and toe fractures only if they are open, compound, or crushed
            -Include all bone fractures of face, skull, or navicular wrist bone
            -Exclude hairline fractures unless described above
        -Complete tendon, ligament, and cartilage tears of the major joints
        -Herniated disks
        -Lacerations resulting in severed tendons and/or a deep wound requiring internal stitches
            -Dont include fingers and toes
        -2nd(10% of body) and 3rd degree burns
        -Eye injuries resulting in eye damage or loss of vision
        -Injections of foreign materials
        -Severe heat exhaustion and all heat stroke cases
        -Dislocation of a major joint
            -Only if requires a doctors help to reposition joint
4. Was a direct control present? 
    - A preemptive measure which mitigates exposure to the specific high-energy source when installed, verified, and used properly
*/

/*
HSIF - High energy sustained injury/fatality
PSIF - Potential sustained injury/fatality
LSIF - Low energy 
Capacity - Incident with a release of high energy in the presence of a direct control where a 
serious injury is not sustained
Success - Condition where a high-energy incident does not occur because of the presence of a 
direct control
Exposure - Condition where high energy is present in the absence of a direct control
Low-Severity - These low-priority incidents are de-prioritized in the model because they did not result in or 
have the potential to result in a SIF

These are sorted based on learning prioritization
in tiers(When multiple are present consider final classification as highest tier): 
1:HSIF,PSIF,LSIF
2: Capcity, sucess, exposure
3: low severity
*/







// IMPLEMENTATION
//     STEP 1: READ IN CSV FILE OF TEST CASES. 
//         SKIP LINE 1.
//         IGNORE FIRST 2 COLUMN VALUES
//         3RD COMMA SEPARATED VALUE = REVIEW (NEED TO CLASSIFY)
        
//     STEP 2: IMPLEMENT CLASSIFIER
        
//     STEP 3: TRAINING ALGORITHM/MODEL REFINEMENT
//         TRAIN CLASSIFIER USING TEST CASES BEFORE PREDICTION

//     STEP 4: PREDICTION
//         HOW TO PREDICT?? Possibly Log-propbability algorithm if possible
        
//     STEP 5: READ IN CSV FILE OF REAL REVIEWS FOR TESTING. 
//         SKIP LINE 1.
//         IGNORE FIRST 2 COLUMN VALUES
//         3RD COMMA SEPARATED VALUE = REVIEW (NEED TO CLASSIFY)
    
        