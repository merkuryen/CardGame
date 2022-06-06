#include <iostream>
#include <string>
#include <vector>
#include <ctime>



class Card {
protected:
    std::string name;
    std::string type;
    std::string color;
    bool isTapped = false;
    std::string manaCost;
    char mana;
    int maxHP;
    bool Trample;
    bool FirstStrike;
    int attackPower;

public:
    Card() {}
    Card(std::string n) :name(n) {}
    Card(std::string n, std::string col) :name(n), color(col) {}
    Card(std::string n, std::string col, char mn) :name(n), color(col), mana(mn) {}
    Card(std::string n, std::string col, std::string mc) :name(n), color(col), manaCost(mc) {}
    Card(std::string n, std::string col, std::string mc, int pow, int hp, bool tr, bool fs) :name(n), color(col), manaCost(mc), attackPower(pow), maxHP(hp), Trample(tr), FirstStrike(fs) {}
    std::string getName() {
        return name;
    }
    bool getTapped() {
        return isTapped;
    }
    void setTapped(bool t) {
        this->isTapped = t;
    }
    std::string getType() {
        return type;
    }
    std::string getColor() {
        return color;
    }
    virtual void play() {};
    std::string getManaCost() {
        return manaCost;
    }
    void setManaCost(std::string c) {
        this->manaCost = c;
    };

    void getDescriptionCreature() {
        std::cout << "Attack Power: " << attackPower << " Max HP: " << maxHP << " ";
        if (FirstStrike == true) {
            std::cout << "First Strike";
        }
        if (Trample == true) {
            std::cout << "Trample";
        }
    }
    char getMana() {
        return mana;
    }
    int getHP() {
        return maxHP;
    }

    int getAttackPower() {
        return attackPower;
    }


};

class landCard : public Card {
public:
    landCard();
    landCard(std::string n, std::string col, char mn) : Card(n, col, mn) {
        type = "Land";
        isTapped = false;
    }
};



class creatureCard : public Card {
protected:


public:
    creatureCard(std::string n, std::string mc, std::string col, int pow, int hp, bool tr, bool fs) : Card(n, col, mc, pow, hp, tr, fs) {
        isTapped = false;
        type = "Creature";
    }
    int getAttackPower() {
        return attackPower;
    }


};

class Effect {
public:
    virtual void activate() {}
};

class DestroyCreatureEffect : public Effect {
public:
    void activate() {}
};

class DestroyLandEffect : public Effect {
public:
    void activate() {}
};

class DestroyEnhancementEffect : public Effect {
public:
    void activate() {}
};

class GainCreatureEffect : public Effect {
public:
    void activate() {}
};
class LoseCreatureEffect : public Effect {
    // Get -1 Power and HP
public:
    void activate() {}
};

class DealDamage :public Effect {
public:
    void activate() {}
};

class MoveCreaturetoHand : public Effect {
public:
    void activate() {}
};

class CreatureGetsLosesFirstStrike : public Effect {
    bool method; // true = gets, false = loses
public:
    void activate() {}
};

class CreatureGetsLosesTrample : public Effect {
    bool method; // true = gets, false = loses
public:
    void activate() {}
};



class enchantmentCard : public Card {
protected:
    Effect efect;
public:
    enchantmentCard(std::string n, std::string col, std::string mc, Effect efc) :Card(n, col, mc), efect(efc) {
        type = "Enchantment";
    }
};

class sorceryCard : public Card {
protected:
    Effect efect;
public:
    sorceryCard(std::string n, std::string col, std::string mc, Effect efc) :Card(n, col, mc), efect(efc) {
        type = "Sorcery";
    }
};




class Player {

protected:
    std::string playerName;
    int HP = 15;
    std::vector<Card> hand;
    std::vector<Card> deck;
    std::vector<Card> inPlay;
    std::vector<Card> discard;
    std::string mana = "";

public:
    Player(std::string n) :playerName(n) {
        createDeck(deck);
        shuffle(deck);
    }

    int getHP() {
        return HP;
    }
    void setHP(int hp) {
        this->HP = hp;
    }
    std::string getPlayerName() {
        return playerName;
    }
    int getPlayerDeckSize() {
        return deck.size();
    }
    int getPlayerHandSize() {
        return hand.size();
    }


    void createDeck(std::vector<Card>& deck) {

        if (playerName == "Player #1") {
            // PLAYER #1 DECK

        //---------------Land Cards ----------------
            for (int i = 0; i < 5; i++) {
                deck.push_back(landCard("Plains", "white", 'W'));
            }
            for (int i = 0; i < 3; i++) {
                deck.push_back(landCard("Forest", "green", 'G'));
            }

            deck.push_back(landCard("Island", "Blue", 'L'));
            //-----------------------------------------

            //---------------Creature Cards ----------------

            for (int i = 0; i < 3; i++) {
                deck.push_back(creatureCard("Soldier", "W", "White", 1, 1, false, false));
            }
            for (int i = 0; i < 2; i++) {
                deck.push_back(creatureCard("Armored Pegasus", "1W", "White", 1, 2, false, false));
            }
            for (int i = 0; i < 2; i++) {
                deck.push_back(creatureCard("White King", "WW", "White", 2, 2, false, true));
            }
            deck.push_back(creatureCard("Angry Bear", "2G", "Green", 3, 2, true, false));
            deck.push_back(creatureCard("Guard", "2W", "White", 2, 5, false, false));
            deck.push_back(creatureCard("Warewolf", "2GW", "Green", 4, 6, true, false));
            //-----------------------------------------------

            //---------------Sorcery Cards ----------------
            deck.push_back(sorceryCard("Disenchant", "White", "1W", DestroyEnhancementEffect()));
            deck.push_back(sorceryCard("Lightning Bolt", "Green", "1G", DealDamage()));
            for (int i = 0; i < 2; i++) {
                deck.push_back(sorceryCard("Flood", "Green", "1GW", DestroyLandEffect()));
            }
            //-----------------------------------------------

            //---------------Enhancement Cards ----------------
            deck.push_back(enchantmentCard("Rage", "Green", "G", CreatureGetsLosesTrample()));
            deck.push_back(enchantmentCard("Holy War", "White", "1W", GainCreatureEffect()));
            deck.push_back(enchantmentCard("Holy Light", "White", "1W", GainCreatureEffect()));
            //-----------------------------------------------
        }
        else {
            // PLAYER #2 DECK

            //---------------Land Cards ----------------
            for (int i = 0; i < 5; i++) {
                deck.push_back(landCard("Swamp", "Black", 'B'));
            }

            for (int i = 0; i < 3; i++) {
                deck.push_back(landCard("Mountain", "Red", 'R'));
            }
            deck.push_back(landCard("Island", "Blue", 'L'));
            //-----------------------------------------

            //---------------Creature Cards ----------------

            for (int i = 0; i < 3; i++) {
                deck.push_back(creatureCard("Skeleton", "B", "Black", 1, 1, false, false));
            }
            for (int i = 0; i < 2; i++) {
                deck.push_back(creatureCard("Ghost", "1B", "Black", 2, 1, false, false));
            }
            for (int i = 0; i < 2; i++) {
                deck.push_back(creatureCard("Black Knight", "BB", "Black", 2, 2, false, true));
            }
            deck.push_back(creatureCard("Orc Maniac", "2R", "Red", 4, 1, false, false));
            deck.push_back(creatureCard("Hobgoblin", "1RB", "Red", 3, 3, false, false));
            deck.push_back(creatureCard("Vampire", "3B", "Black", 6, 3, false, false));
            //-----------------------------------------------

            //---------------Sorcery Cards ----------------
            deck.push_back(sorceryCard("Reanimate", "Black", "B", MoveCreaturetoHand()));
            deck.push_back(sorceryCard("Plague", "Black", "2B", DealDamage()));
            for (int i = 0; i < 2; i++) {
                deck.push_back(sorceryCard("Terror", "Black", "1B", DestroyCreatureEffect()));
            }
            //-----------------------------------------------

            //---------------Enhancement Cards ----------------
            deck.push_back(enchantmentCard("Unholy War", "Black", "1B", GainCreatureEffect()));
            deck.push_back(enchantmentCard("Restrain", "Red", "2R", CreatureGetsLosesTrample()));
            deck.push_back(enchantmentCard("Slow", "Black", "B", GainCreatureEffect()));
            //-----------------------------------------------

        }

    }
    void shuffle(std::vector<Card>& deck) {
        int randomSeed;
        srand(time(NULL));
        randomSeed = rand() % 100;
        srand(randomSeed);
        Card temp;
        std::vector<Card> newDeck;

        while (deck.size() != 0) {
            newDeck.push_back(deck.back());
            deck.pop_back();
        }

        for (int i = 0; i < newDeck.size(); i++) {

            for (int j = 0; j < newDeck.size(); j++) {

                if (rand() % 2 == 0) {
                    temp = newDeck[i];
                    newDeck[i] = newDeck[j];
                    newDeck[j] = temp;

                }
            }
        }

        while (newDeck.size() > 0) {
            deck.push_back(newDeck.back());
            newDeck.pop_back();
        }

    }
    void drawCard() {
        if (hand.size() < 7) {
            if (deck.size() > 0) {
                hand.push_back(deck.back());
                deck.pop_back();
            }
        }
    }

    void untapAllCards() {
        if (!getPlay().empty()) {
            for (int i = 0; i < inPlay.size(); i++) {
                inPlay[i].setTapped(false);
            }
        }
        mana = "";
    }

    void discardCard() {

    }
    void playCard(int cardNumber) {
        if (!getPlay().empty()) {
            if (inPlay[cardNumber - 1].getType() == "Land" && !inPlay[cardNumber - 1].getTapped()) {
                mana.push_back(inPlay[cardNumber - 1].getMana());
                inPlay[cardNumber - 1].setTapped(true);
            }
            if (inPlay[cardNumber - 1].getType() == "Creature" && !inPlay[cardNumber - 1].getTapped()) {
                int choice;
                std::cout << "Select a card you want to attack: " << std::endl;
                std::cin >> choice;





            }
        }

    }
    void summonCard(int i) {
        if (i <= hand.size()) {
            std::string manaCostofCard = hand[i - 1].getManaCost();
            std::string copy = manaCostofCard;
            std::string manaCopy = mana;
            for (int i = copy.length() - 1; i >= 0; i--) {
                for (int j = 0; j < manaCopy.length(); j++) {
                    if (manaCopy[j] == copy[i]) {
                        manaCopy.replace(j, 1, "");
                        copy.replace(i, 1, "");
                    }
                    else if (copy == "1") {
                        manaCopy.replace(j, 1, "");
                        copy.replace(i, 1, "");
                    }
                    else if (copy == "2") {
                        manaCopy.replace(j, 2, "");
                        copy.replace(i, 2, "");
                    }
                    else if (copy == "3") {
                        manaCopy.replace(j, 3, "");
                        copy.replace(i, 3, "");
                    }
                }
            }

            if (copy == "") {
                mana = manaCopy;

                inPlay.push_back(hand[i - 1]);
                hand.erase(hand.begin() + i - 1);

            }

        }
    }

    void displayHand() {
        std::cout << "#-----" << playerName << "'s Hand-----" << std::endl;
        for (int i = 0; i < hand.size(); i++) {

            std::cout << i + 1 << ". " << hand[i].getName() << " (" << hand[i].getType() << " " << hand[i].getColor() << " " << hand[i].getManaCost() << " ";
            if (hand[i].getType() == "Creature") {
                hand[i].getDescriptionCreature();
            }
            if (hand[i].getType() == "Land") {
                std::cout << hand[i].getMana();
            }


            std::cout << ")" << std::endl;
        }
        std::cout << "#---------------------------------" << std::endl;
        std::cout << std::endl;

    }

    void displayPlay() {
        std::cout << "#-----" << playerName << "'s Cards-----" << std::endl;
        for (int i = 0; i < inPlay.size(); i++) {

            std::cout << i + 1 << ". " << inPlay[i].getName() << " (" << inPlay[i].getType() << " " << inPlay[i].getColor() << " ";

            if (inPlay[i].getTapped()) {
                std::cout << "Tapped";
            }
            std::cout << ")" << std::endl;
        }
        std::cout << "#---------------------------------" << std::endl;
        std::cout << std::endl;
    }

    void displayDeck() {
        for (int i = 0; i < deck.size(); i++) {
            std::cout << i + 1 << ". " << deck[i].getName() << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<Card>& getHand() {
        return hand;
    }
    std::vector<Card>& getDeck() {
        return deck;
    }
    std::vector<Card> getPlay() {
        return inPlay;
    }

    std::string getMana() {
        return mana;
    }
    void attackCard(int cardNum, int attackPower, int maxHP) {
        if (inPlay[cardNum - 1].getHP() < attackPower) {
            std::cout << inPlay[cardNum - 1].getName() << " is destroyed. " << std::endl;
            discard.push_back(inPlay[cardNum - 1]);
            inPlay.erase(inPlay.begin() + cardNum - 1);
        }

    }

    std::string getCardTypeinPlay(int num) {
        return inPlay[num - 1].getType();
    }
    int getAttackPowerinPlay(int num) {
        return inPlay[num - 1].getAttackPower();
    }
    int getMaxHPinPlay(int num) {
        return inPlay[num - 1].getHP();
    }


};


void attack(Player p, int cardNum, int attackPower, int maxHP) {
    p.attackCard(cardNum, attackPower, maxHP);
}



int main() {
    Player player1("Player #1");
    Player player2("Player #2");
    int choice;
    int round = 1;
    for (int i = 0; i < 4; i++) {
        player1.drawCard();
        player2.drawCard();
    }

    while (player1.getHP() > 0 && !player1.getDeck().empty() && player2.getHP() > 0 && !player2.getDeck().empty()) {
        std::cout << "#----------Round " << round << " Start ------------ " << std::endl;
        round++;
        std::cout << player1.getPlayerName() << "'s turn!!! " << std::endl;
        player1.drawCard(); // Draw Phase for Player #1
        player1.untapAllCards(); // untap Phase for Player #1

        do {
            std::cout << "-----Cards in Play-----" << std::endl;
            std::cout << player2.getPlayerName() << " HP: " << player2.getHP() << " Mana: " << player2.getMana() << std::endl;
            player2.displayPlay();
            std::cout << player1.getPlayerName() << " HP: " << player1.getHP() << " Mana: " << player1.getMana() << std::endl;
            player1.displayPlay();
            player1.displayHand();

            std::cout << "1. Summon Card" << std::endl;
            std::cout << "2. Play Card" << std::endl;
            std::cout << "3. Pass Turn" << std::endl;
            std::cin >> choice;
            int cardNumber;
            switch (choice) {
            case 1:
                std::cout << "Please select which number card you summon: " << std::endl;
                std::cin >> cardNumber;
                player1.summonCard(cardNumber);
                break;
            case 2:
                std::cout << "Please select which card you play: " << std::endl;
                std::cin >> cardNumber;
                if (player1.getCardTypeinPlay(cardNumber) == "Creature") {
                    int cardNum;
                    std::cout << "Which card do you want to attack: " << std::endl;
                    std::cin >> cardNum;
                    attack(player2, cardNum, player1.getAttackPowerinPlay(cardNumber), player1.getMaxHPinPlay(cardNumber));
                }
                player1.playCard(cardNumber);
                break;
            case 3:
                break;
            }

        } while (choice != 3);


        std::cout << player2.getPlayerName() << "'s turn!!! " << std::endl;
        player2.drawCard(); // Draw Phase for Player #2
        player2.untapAllCards(); // untap Phase for Player #2

        do {
            std::cout << "-----Cards in Play-----" << std::endl;
            std::cout << player1.getPlayerName() << " HP: " << player1.getHP() << " Mana: " << player1.getMana() << std::endl;
            player1.displayPlay();
            std::cout << player2.getPlayerName() << " HP: " << player2.getHP() << " Mana:" << player2.getMana() << std::endl;
            player2.displayPlay();
            player2.displayHand();

            std::cout << "1. Summon Card" << std::endl;
            std::cout << "2. Play Card" << std::endl;
            std::cout << "3. Pass Turn" << std::endl;
            std::cin >> choice;
            switch (choice) {
            case 1:
                int cardNumber;
                std::cout << "Please select which number card you summon: " << std::endl;
                std::cin >> cardNumber;
                player2.summonCard(cardNumber);
                break;
            case 2:
                std::cout << "Please select which card you play: " << std::endl;
                std::cin >> cardNumber;
                if (player2.getCardTypeinPlay(cardNumber) == "Creature") {
                    int cardNum;
                    std::cout << "Which card do you want to attack: " << std::endl;
                    std::cin >> cardNum;
                    attack(player1, cardNum, player2.getAttackPowerinPlay(cardNumber), player2.getMaxHPinPlay(cardNumber));
                }
                player2.playCard(cardNumber);
                break;
            case 3:
                break;
            }

        } while (choice != 3);

    }

    if (player1.getHP() < 1 || player1.getDeck().empty()) {
        std::cout << player2.getPlayerName() << " is winner!!!" << std::endl;
    }
    else if (player2.getHP() < 1 || player2.getDeck().empty()) {
        std::cout << player1.getPlayerName() << " is winner!!!" << std::endl;
    }


    return 0;
}