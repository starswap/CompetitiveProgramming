//Use C++20 to run this code

//Method:
//   - It never matters which outfit each model is changed into because a change is a change. The fact that the first change is free could jeopardise this but it doesn't because when a model is changed for the first time they become the same as all other models that have already been changed. 
//   - Therefore, at each round, if a model can stay the same, keep themt the same. If they have to change, allocate them to any of the new outifts.  
//   - However we have to explicitly deal with the case where two different models could both be kept the same, i.e. the case 1 1 -> 1 3 for example. In this case we always want to change a new model if we can as the first change is free, so if we make sure to consider all of the new models for changes first (i.e. all of the old models for staying the same first) we will get an optimum.
//   - Track each change and the answer will be the number of changes made in total, minus the number of models changed. 
 

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d",&T);
  
  for (int t=1;t<=T;++t) {
    int ans, nRounds, mModels; //as detailled in problem description
    scanf("%d %d",&nRounds,&mModels);
    
    int changes = 0; //total number of changes required
    vector<multiset<int>> outfits(nRounds+1);  //(for each round, the outfits that need to be displayed)
    vector<int> modelOutfits(mModels); //What outfit each model is currently wearing
    multimap<int,int,greater<int>> indices; //maps the number of times each model has changed to their index, enabling us to iterate over the models in order of number of changes decreasing, so that the models which have been changed the most already get the first "say" to not be changed again. 

    //Read input
    for (int j=0;j<=nRounds;++j) {
      for (int i=0;i<mModels;++i) {
        int style;
        scanf("%d",&style);
        outfits[j].insert(style); //Each round's outfits to dispaly
        if (j == 0) {//prior to the first round - what are they arriving in?
          modelOutfits[i] = style;
          indices.emplace(0,i); //We do this initialisation here as we only want to do it once. (each model has been changed 0 times initially)
        }
      }
    }

    //Go through all of the rounds
    for (int j=0;j<nRounds;++j) {
      multimap<int,int,greater<int>> indices2; //Rebuild the indices array on each round and "move" it back afterwards so we don't mutate something we are iterating over.
      vector<bool> thisChanged(mModels,false); //Which models have we changed this round? So we know which ones need new outfits
      for (auto [timesChanged, i] : indices) { //iterate over models in order of previous changes increasing
        if (outfits[j+1].contains(modelOutfits[i])) { //no need to change the model as their style is needed in the next round
          outfits[j+1].erase(outfits[j+1].find(modelOutfits[i])); //Remove so we don't double count (i.e. 1 1 -> 1 3 requires 1 change)
          indices2.emplace(timesChanged,i); //no change to this
        }
        else { //need to change this model to something; don't care what.
          thisChanged[i] = true; //we have changed them once this round
          changes += 1; //total changes 
          indices2.emplace(timesChanged+1,i); //update the ordering in which we iterate (could probably be done via a comparator-based dynamically updating set with no copies)
        }
      }
      
      indices = indices2; //move it over/
      
      auto it = outfits[j+1].begin(); //Will be used to iterate over all of the outfits we are changing /into/; these are the only ones left in outfits[j+1].
      for (int i=0;i<mModels;++i) { //for every model
        if (thisChanged[i]) { //if we needed to change them this time
          modelOutfits[i] = *it; //allocate them the next available outfit
          ++it; //move on so that we don't allocate this outfit again.
        }
      }      
    }

    //Answer is total number of changes minus 1 for each model we changed; first change free.
    ans = changes;
    for (auto [timesChanged, i] : indices) {
      ans -= (timesChanged > 0);
    }
    printf("Case #%d: %d\n",t,ans);
  }
}
