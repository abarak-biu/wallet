#include <vector>
#include <string>


constexpr int NUM_BIP39_WORDS = 2048;

class SeedPhraseGenerator {
public:
    static std::vector<std::string> generateSeedPhrase();

private:
    static SeedPhraseGenerator & instance() {
        static SeedPhraseGenerator theInstance;
        return theInstance;
    };

    SeedPhraseGenerator();
    void loadBip39WordsFromFile();
    std::vector<std::string> innerGenerareSeedPhrase(int numWordsToGenerate);

    std::vector<std::string> m_words; 
};