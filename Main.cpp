#include <iostream>
#include<cstdint>
#include <vector>
using namespace std;

class Bowling {
private:
    uint16_t finalScore;
    vector<uint16_t> score;
    bool isStrike(uint8_t index) {
        return score[index] == 10;
    }
    bool isSpare(uint8_t index) {
        return score[index] + score[index + 1] == 10;
    }
    uint16_t strikeBonus(uint8_t index) {
        return score[index + 1] + score[index + 2];
    }
    uint16_t spareBonus(uint8_t index) {
        return score[index + 2];
    }
    uint16_t sumOfPinsInFrame(uint8_t index) {
        return score[index] + score[index + 1];
    }
public:
    uint16_t calculateScore();
    uint8_t firstTry;
    uint8_t secondTry;
    uint16_t roundNumber;
    void addRound(uint16_t input) {
        score.push_back(input);
    }
    Bowling(){
        finalScore = 0;
        roundNumber = 0;

    }
     ~Bowling(){
        finalScore = 0;
        roundNumber = 0;
    }
};


uint16_t Bowling::calculateScore() {
    uint8_t scoreIndex = 0;
    uint16_t roundIndex = 0;

    for (uint16_t i = 0; i < score.size(); ++i) {
        cout << " "<< score[i];
    }
    cout << endl;
    for (roundIndex = 1; roundIndex < 10; roundIndex++) {
        if (isStrike(scoreIndex)) {
            finalScore += score[scoreIndex] + strikeBonus(scoreIndex);
            scoreIndex+= 1;
            cout << "Round: " << roundIndex << " Score:" << finalScore << endl;
        } else if (isSpare(scoreIndex))  {
            finalScore += sumOfPinsInFrame(scoreIndex) + spareBonus(scoreIndex);
            scoreIndex += 2;
            cout << "Round: " << roundIndex << " Score:" << finalScore << endl;
        } else {
            finalScore += sumOfPinsInFrame(scoreIndex);
            scoreIndex += 2;
            cout << "Round: " << roundIndex << " Score:" << finalScore << endl;
        }
    }
    finalScore += score[scoreIndex] + score[scoreIndex + 1] + score[scoreIndex + 2];
    cout << "Round: " << roundIndex << " Final Score:" << finalScore << endl;

    return finalScore;
}

int main()
{
    Bowling B;
    uint8_t lastRoundTries = 0;
    cout << "Hello world!" << endl;
    cout << "Bowling Game Enter Score 0-9, x = strike, / = spare, Any other character to EXIT" << endl;
    B.roundNumber++;
    B.firstTry = 255;
    B.secondTry = 255;
    while (B.roundNumber <= 10) {
        char ch = 'E';
        cout << "Round : " << B.roundNumber;
        cout << "  Enter Input: ";
        cin >> ch;
        if ('x' == ch) {
            B.firstTry = 10;
            B.secondTry = 0;
            B.addRound(10);
            B.firstTry = 255;
            B.secondTry = 255;
            if (B.roundNumber == 10) {
                lastRoundTries++;
            } else {
                cout << "Round Over: " << B.roundNumber << endl;
                B.roundNumber++;
            }
        } else if ('/' == ch) {
            B.secondTry = 10 - B.firstTry;
            B.addRound(B.secondTry);
            B.firstTry = 255;
            B.secondTry = 255;
            if (B.roundNumber == 10) {
                lastRoundTries++;
            } else {
                cout << "Round Over: " << B.roundNumber << endl;
                B.roundNumber++;
            }
        } else if ((ch >= '0') && (ch <= '9')) {
            ch = ch - '0';
            B.addRound(static_cast<uint16_t>(ch));
            if (B.roundNumber == 10) {
                B.firstTry = static_cast<uint16_t>(ch);
                lastRoundTries++;
            } else {
                if (B.firstTry < 10) {
                    cout << "Round Over: " << B.roundNumber << endl;
                    B.roundNumber++;
                    //calculateScore();
                    B.firstTry = 255;
                    B.secondTry = 255;
                } else if (B.firstTry == 255) {
                    B.firstTry = static_cast<uint16_t>(ch);
                }
            }
        } else {
            cout << "EXIT" << endl;
            break;
        }
        if ((B.roundNumber == 10) && (lastRoundTries == 3)) {
            B.calculateScore();
            cout << "Last Round Over: " << B.roundNumber << endl;
            B.roundNumber++;
        }
    };
    return 0;
}
