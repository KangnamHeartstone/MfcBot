
class CardData {
	int attack, health;
	CString cardID, cardName;
	CString imgUrl;
public:
	CardData(CString cardID = CString(""), CString cardName = CString(""), CString imgUrl = CString(""), int attack = 0, int health = 0) {
	}

	int GetAttack() {
		return attack;
	}

	int GetHealth() {
		return health;
	}

	CString GetCardID() {
		return cardID;
	}

	CString GetCardName() {
		return cardName;
	}

	CString GetImgUrl() {
		return imgUrl;
	}

	void SetAttack(int attack) {
		this->attack = attack;
	}

	void SetHealth(int health) {
		this->health = health;
	}

	void SetCardID(CString cardID) {
		this->cardID = cardID;
	}

	void SetCardName(CString cardName) {
		this->cardName = cardName;
	}

	void SetImgUrl(CString imgUrl) {
		this->imgUrl = imgUrl;
	}
};