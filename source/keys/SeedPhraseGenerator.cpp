#include "SeedPhraseGenerator.h"
#include "Random.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

 std::vector<std::string> SeedPhraseGenerator::generateSeedPhrase() {
    return SeedPhraseGenerator::instance().innerGenerareSeedPhrase(12);
 }
 
SeedPhraseGenerator::SeedPhraseGenerator() {
    loadBip39WordsFromFile();
}

std::vector<std::string> SeedPhraseGenerator::innerGenerareSeedPhrase(int numWordsToGenerate) {
    auto wordIndexes = Random::sampleNfromRange(numWordsToGenerate,NUM_BIP39_WORDS);
    std::vector<string> seedPhrase(numWordsToGenerate); 

    std::transform(wordIndexes.cbegin(), wordIndexes.cend(),
                   seedPhrase.begin(),
                   [this](int idx) { return m_words[idx]; });

    return seedPhrase;
}

void SeedPhraseGenerator::loadBip39WordsFromFile() {
   fstream newfile;
   newfile.open("words.txt",ios::in); 

   if (!newfile.is_open())  {
      throw std::invalid_argument("BIP39 words file not found");
   }
   string word;
   while(getline(newfile, word)){ 
      m_words.push_back(word);
   }

   if (m_words.size() != NUM_BIP39_WORDS) {
      throw std::invalid_argument("BIP39 words file does not contain 2048 values");
   } 
   newfile.close();    
   
}
