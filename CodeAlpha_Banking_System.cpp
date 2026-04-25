#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

const string DATA_FILE = "bank_data.txt";

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(string prompt) {
	int value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin.fail()) {
			cout << "Invalid input. Please enter a number." << endl;
			clearInput();
		}
		else {
			clearInput();
			return value;
		}
	}
}

float readFloat(string prompt) {
	float value;
	while (true) {
		cout << prompt;
		cin >> value;
		if (cin.fail()) {
			cout << "Invalid input. Please enter a valid amount." << endl;
			clearInput();
		}
		else {
			clearInput();
			return value;
		}
	}
}

char readChar(string prompt) {
	char value;
	cout << prompt;
	cin >> value;
	clearInput();
	return value;
}

string readLine(string prompt) {
	string value;
	cout << prompt;
	getline(cin, value);
	return value;
}


class Transaction {

private:

	time_t timeStamp;
	string transType;
	float Amount;
	string TransID;

	static int dCount;
	static int wCount;
	static int tCount;
	char id[3] = { 'D', 'W', 'T' };

public:

	Transaction(time_t timeStamp, string transType, float amount) {

		this->timeStamp = timeStamp;
		this->transType = transType;
		this->Amount = amount;

		if (transType[0] == id[0]) {
			dCount++;
			this->TransID = string(1, id[0]) + to_string(dCount);
		}
		else if (transType[0] == id[1]) {
			wCount++;
			this->TransID = string(1, id[1]) + to_string(wCount);
		}
		else {
			tCount++;
			this->TransID = string(1, id[2]) + to_string(tCount);
		}
	}

	Transaction(string transID, string transType, float amount, time_t timeStamp) {
		this->TransID = transID;
		this->transType = transType;
		this->Amount = amount;
		this->timeStamp = timeStamp;
	}

	time_t getTime() {
		return timeStamp;
	}
	string getTransType() {
		return transType;
	}
	float getAmount() {
		return Amount;
	}
	string getTransID() {
		return TransID;
	}

	static void setDCount(int val) { dCount = val; }
	static void setWCount(int val) { wCount = val; }
	static void setTCount(int val) { tCount = val; }
	static int getDCount() { return dCount; }
	static int getWCount() { return wCount; }
	static int getTCount() { return tCount; }

	void setTime() {
		timeStamp = time(nullptr);
	}
	void setTransType(string type) {
		transType = type;
	}
	void setAmount(float amount) {
		Amount = amount;
	}

	void transInfo() {
		cout << "Transaction ID: " << TransID << endl;
		cout << "Transaction Type: " << transType << endl;
		cout << "Transaction Amount: " << Amount << endl;
	}

	void saveToFile(ofstream& file) {
		file << "TRANS" << endl;
		file << "ID " << TransID << endl;
		file << "TYPE " << transType << endl;
		file << "AMOUNT " << Amount << endl;
		file << "END_TRANS" << endl;
	}
};

int Transaction::dCount = 0;
int Transaction::wCount = 0;
int Transaction::tCount = 0;


class Account {

private:

	string accNum;
	float accBal;
	int accOwner;
	vector<Transaction> trans;
	string accType;

	char accId[3] = { 'S', 'C', 'F' };

	static int sCount;
	static int cCount;
	static int fCount;

public:

	Account(string accType, float accBal, int accOwner) {
		this->accType = accType;
		this->accBal = accBal;
		this->accOwner = accOwner;

		if (accType[0] == accId[0]) {
			sCount++;
			this->accNum = string(1, accId[0]) + to_string(sCount);
		}
		else if (accType[0] == accId[1]) {
			cCount++;
			this->accNum = string(1, accId[1]) + to_string(cCount);
		}
		else {
			fCount++;
			this->accNum = string(1, accId[2]) + to_string(fCount);
		}
	}

	Account(string accNum, string accType, float accBal, int accOwner) {
		this->accNum = accNum;
		this->accType = accType;
		this->accBal = accBal;
		this->accOwner = accOwner;
	}

	string getAccNum() { return accNum; }
	float  getAccBal() { return accBal; }
	int    getAccOwn() { return accOwner; }
	string getAccType() { return accType; }
	vector<Transaction> getAccTrans() { return trans; }

	static void setSCount(int val) { sCount = val; }
	static void setCCount(int val) { cCount = val; }
	static void setFCount(int val) { fCount = val; }
	static int getSCount() { return sCount; }
	static int getCCount() { return cCount; }
	static int getFCount() { return fCount; }

	void setAccNum(string account) { accNum = account; }
	void setAccBal(float balance) { accBal = balance; }
	void setAccOwn(int owner) { accOwner = owner; }

	void addTrans(Transaction obj) {
		trans.push_back(obj);
	}

	void Deposit(float amount) {
		accBal = accBal + amount;
		Transaction t(time(nullptr), "Deposit", amount);
		trans.push_back(t);
	}

	void Withdraw(float amount) {
		if (amount > accBal) {
			cout << "Not sufficient balance!" << endl;
			return;
		}
		else {
			accBal = accBal - amount;
			Transaction t(time(nullptr), "Withdrawal", amount);
			trans.push_back(t);
		}
	}

	void displayTrans() {
		int size = (int)trans.size();
		cout << "\n--- Transaction History ---" << endl;
		if (size == 0) {
			cout << "No transactions yet." << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			trans[i].transInfo();
			cout << endl;
		}
	}

	void displayAcc() {
		cout << "Account Number: " << accNum << endl;
		cout << "Account Type:   " << accType << endl;
		cout << "Balance:        " << accBal << endl;
		cout << "Transactions:   " << trans.size() << endl;
	}

	void saveToFile(ofstream& file) {
		file << "ACCOUNT" << endl;
		file << "NUM " << accNum << endl;
		file << "TYPE " << accType << endl;
		file << "BAL " << accBal << endl;
		file << "OWNER " << accOwner << endl;
		file << "TRANSACTIONS " << trans.size() << endl;
		for (int i = 0; i < (int)trans.size(); i++) {
			trans[i].saveToFile(file);
		}
		file << "END_ACCOUNT" << endl;
	}
};

int Account::sCount = 0;
int Account::cCount = 0;
int Account::fCount = 0;


class Customer {

private:

	int cusID;
	string cusName;
	int cusAge;
	char cusGender;
	string cusContact;
	vector<Account> accounts;

	static int cID;

public:

	Customer(string cusName, string cusContact, int cusAge, char cusGender) {
		this->cusName = cusName;
		this->cusAge = cusAge;
		this->cusGender = cusGender;
		this->cusContact = cusContact;
		this->cusID = cID;
		cID++;
	}

	Customer(int cusID, string cusName, string cusContact, int cusAge, char cusGender) {
		this->cusID = cusID;
		this->cusName = cusName;
		this->cusAge = cusAge;
		this->cusGender = cusGender;
		this->cusContact = cusContact;
	}

	static void setCID(int val) { cID = val; }
	static int  getCID() { return cID; }

	void setCusName(string name) { cusName = name; }
	void setContact(string contact) { cusContact = contact; }
	void setAge(int age) { cusAge = age; }
	void setGender(char gender) { cusGender = gender; }

	int    getCusID() { return cusID; }
	string getCusName() { return cusName; }
	string getCusContact() { return cusContact; }
	int    getCusAge() { return cusAge; }
	char   getCusGender() { return cusGender; }
	vector<Account>& getCusAccounts() { return accounts; }

	void createAcc() {
		int accType = readInt("\nSelect Account Type (1. Savings  2. Current  3. Fixed Deposit): ");

		if (accType < 1 || accType > 3) {
			cout << "Invalid option!" << endl;
			return;
		}

		float accBal = 0;
		char choice = readChar("Make an initial deposit? (Y/N): ");

		if (choice == 'Y' || choice == 'y') {
			accBal = readFloat("Enter deposit amount: ");
			if (accBal < 0) {
				cout << "Invalid amount. Starting balance set to 0." << endl;
				accBal = 0;
			}
		}

		switch (accType) {
		case 1: {
			Account acc("Savings", accBal, cusID);
			accounts.push_back(acc);
			cout << "Savings account created! Account Number: " << accounts.back().getAccNum() << endl;
			break;
		}
		case 2: {
			Account acc("Current", accBal, cusID);
			accounts.push_back(acc);
			cout << "Current account created! Account Number: " << accounts.back().getAccNum() << endl;
			break;
		}
		case 3: {
			Account acc("Fixed Deposit", accBal, cusID);
			accounts.push_back(acc);
			cout << "Fixed Deposit account created! Account Number: " << accounts.back().getAccNum() << endl;
			break;
		}
		}
	}

	void transferSelf(float amount, string accNum1, string accNum2) {
		int idx1 = -1, idx2 = -1;

		for (int i = 0; i < (int)accounts.size(); i++) {
			if (accounts[i].getAccNum() == accNum1) idx1 = i;
			if (accounts[i].getAccNum() == accNum2) idx2 = i;
		}

		if (idx1 == -1 && idx2 == -1) {
			cout << "Both account numbers not found! Transfer failed." << endl;
			return;
		}
		if (idx1 == -1) {
			cout << "Account " << accNum1 << " not found! Transfer failed." << endl;
			return;
		}
		if (idx2 == -1) {
			cout << "Account " << accNum2 << " not found! Transfer failed." << endl;
			return;
		}
		if (accNum1 == accNum2) {
			cout << "Cannot transfer to the same account!" << endl;
			return;
		}
		if (accounts[idx1].getAccBal() < amount) {
			cout << "Not enough balance in account " << accNum1 << "!" << endl;
			return;
		}

		accounts[idx1].Withdraw(amount);
		accounts[idx2].Deposit(amount);

		cout << "Transfer successful!" << endl;
		cout << "Withdrew " << amount << " from " << accNum1 << endl;
		cout << "Deposited " << amount << " to " << accNum2 << endl;
	}

	void displayInfo() {
		cout << "\n--- My Profile ---" << endl;
		cout << "Customer ID: " << cusID << endl;
		cout << "Name:        " << cusName << endl;
		cout << "Age:         " << cusAge << endl;
		cout << "Gender:      " << cusGender << endl;
		cout << "Contact:     " << cusContact << endl;
		cout << "Accounts:    " << accounts.size() << endl;
	}

	void saveToFile(ofstream& file) {
		file << "CUSTOMER" << endl;
		file << "ID " << cusID << endl;
		file << "NAME " << cusName << endl;
		file << "AGE " << cusAge << endl;
		file << "GENDER " << cusGender << endl;
		file << "CONTACT " << cusContact << endl;
		file << "ACCOUNTS " << accounts.size() << endl;
		for (int i = 0; i < (int)accounts.size(); i++) {
			accounts[i].saveToFile(file);
		}
		file << "END_CUSTOMER" << endl;
	}
};

int Customer::cID = 1;


class Manager {

private:
	vector<Customer> customers;

public:

	vector<Customer>& getCustomers() { return customers; }

	Manager() {}

	Manager(Customer cust) {
		customers.push_back(cust);
	}

	void addCustomer(Customer cust) {
		customers.push_back(cust);
	}

	Customer* getCustomer(int cusID) {
		for (int i = 0; i < (int)customers.size(); i++) {
			if (customers[i].getCusID() == cusID) {
				return &customers[i];
			}
		}
		return nullptr;
	}

	bool verifyCustomer(int id, string name) {
		for (int i = 0; i < (int)customers.size(); i++) {
			if (customers[i].getCusID() == id && customers[i].getCusName() == name) {
				return true;
			}
		}
		return false;
	}

	void transferOther(float amount, int cusID1, int cusID2, string accT1, string accT2) {
		Customer* c1 = getCustomer(cusID1);
		Customer* c2 = getCustomer(cusID2);

		if (c1 == nullptr) {
			cout << "Customer " << cusID1 << " not found! Transfer failed." << endl;
			return;
		}
		if (c2 == nullptr) {
			cout << "Customer " << cusID2 << " not found! Transfer failed." << endl;
			return;
		}

		int idx1 = -1, idx2 = -1;
		vector<Account>& acc1 = c1->getCusAccounts();
		vector<Account>& acc2 = c2->getCusAccounts();

		for (int i = 0; i < (int)acc1.size(); i++) {
			if (acc1[i].getAccNum() == accT1) idx1 = i;
		}
		for (int i = 0; i < (int)acc2.size(); i++) {
			if (acc2[i].getAccNum() == accT2) idx2 = i;
		}

		if (idx1 == -1) {
			cout << "Account " << accT1 << " not found! Transfer failed." << endl;
			return;
		}
		if (idx2 == -1) {
			cout << "Account " << accT2 << " not found! Transfer failed." << endl;
			return;
		}
		if (acc1[idx1].getAccBal() < amount) {
			cout << "Not enough balance in account " << accT1 << "!" << endl;
			return;
		}

		acc1[idx1].Withdraw(amount);
		acc2[idx2].Deposit(amount);

		cout << "Transfer successful!" << endl;
		cout << "Withdrew " << amount << " from customer " << cusID1 << "'s account " << accT1 << endl;
		cout << "Deposited " << amount << " to customer " << cusID2 << "'s account " << accT2 << endl;
	}

	void saveAllToFile() {
		ofstream file(DATA_FILE);
		if (!file.is_open()) {
			cout << "Warning: Could not save data to file." << endl;
			return;
		}

		file << "COUNTERS" << endl;
		file << "CID " << Customer::getCID() << endl;
		file << "DCOUNT " << Transaction::getDCount() << endl;
		file << "WCOUNT " << Transaction::getWCount() << endl;
		file << "TCOUNT " << Transaction::getTCount() << endl;
		file << "SCOUNT " << Account::getSCount() << endl;
		file << "CCOUNT " << Account::getCCount() << endl;
		file << "FCOUNT " << Account::getFCount() << endl;
		file << "END_COUNTERS" << endl;

		for (int i = 0; i < (int)customers.size(); i++) {
			customers[i].saveToFile(file);
		}

		file.close();
		cout << "Data saved." << endl;
	}

	void loadFromFile() {
		ifstream file(DATA_FILE);
		if (!file.is_open()) {
			return;
		}

		string line;
		while (getline(file, line)) {

			if (line == "COUNTERS") {
				string key;
				int val;
				while (getline(file, line) && line != "END_COUNTERS") {
					key = line.substr(0, line.find(' '));
					val = stoi(line.substr(line.find(' ') + 1));
					if (key == "CID")    Customer::setCID(val);
					else if (key == "DCOUNT") Transaction::setDCount(val);
					else if (key == "WCOUNT") Transaction::setWCount(val);
					else if (key == "TCOUNT") Transaction::setTCount(val);
					else if (key == "SCOUNT") Account::setSCount(val);
					else if (key == "CCOUNT") Account::setCCount(val);
					else if (key == "FCOUNT") Account::setFCount(val);
				}
			}

			else if (line == "CUSTOMER") {
				int    cusID = 0;
				string cusName, cusContact;
				int    cusAge = 0;
				char   cusGender = 'M';

				while (getline(file, line) && line != "ACCOUNTS " + to_string(0)) {
					if (line.substr(0, 3) == "ID ") {
						cusID = stoi(line.substr(3));
					}
					else if (line.substr(0, 5) == "NAME ") {
						cusName = line.substr(5);
					}
					else if (line.substr(0, 4) == "AGE ") {
						cusAge = stoi(line.substr(4));
					}
					else if (line.substr(0, 7) == "GENDER ") {
						cusGender = line[7];
					}
					else if (line.substr(0, 8) == "CONTACT ") {
						cusContact = line.substr(8);
					}
					else if (line.substr(0, 9) == "ACCOUNTS ") {
						break;
					}
				}

				Customer cust(cusID, cusName, cusContact, cusAge, cusGender);

				int numAccounts = 0;
				if (line.substr(0, 9) == "ACCOUNTS ") {
					numAccounts = stoi(line.substr(9));
				}

				for (int a = 0; a < numAccounts; a++) {
					string accNum, accType, accContact;
					float  accBal = 0;
					int    accOwner = 0;

					while (getline(file, line) && line != "TRANSACTIONS " + to_string(0)) {
						if (line == "ACCOUNT") continue;
						else if (line.substr(0, 4) == "NUM ")   accNum = line.substr(4);
						else if (line.substr(0, 5) == "TYPE ")  accType = line.substr(5);
						else if (line.substr(0, 4) == "BAL ")   accBal = stof(line.substr(4));
						else if (line.substr(0, 6) == "OWNER ") accOwner = stoi(line.substr(6));
						else if (line.substr(0, 13) == "TRANSACTIONS ") break;
					}

					Account acc(accNum, accType, accBal, accOwner);

					int numTrans = 0;
					if (line.substr(0, 13) == "TRANSACTIONS ") {
						numTrans = stoi(line.substr(13));
					}

					for (int t = 0; t < numTrans; t++) {
						string transID, transType;
						float  transAmount = 0;


						while (getline(file, line) && line != "END_TRANS") {
							if (line == "TRANS") continue;
							else if (line.substr(0, 3) == "ID ")     transID = line.substr(3);
							else if (line.substr(0, 5) == "TYPE ")   transType = line.substr(5);
							else if (line.substr(0, 7) == "AMOUNT ") transAmount = stof(line.substr(7));
						}

						Transaction trans(transID, transType, transAmount, 0);
						acc.addTrans(trans);
					}

					getline(file, line);
					cust.getCusAccounts().push_back(acc);
				}

				getline(file, line);
				customers.push_back(cust);
			}
		}

		file.close();
	}
};


void showAccountList(Customer* cust) {
	vector<Account>& accs = cust->getCusAccounts();
	if (accs.empty()) {
		cout << "  No accounts found." << endl;
		return;
	}
	for (int i = 0; i < (int)accs.size(); i++) {
		cout << "  " << i + 1 << ". [" << accs[i].getAccNum() << "] "
			<< accs[i].getAccType() << " - Balance: " << accs[i].getAccBal() << endl;
	}
}

void showMainMenu() {
	cout << "\n================================" << endl;
	cout << "           MAIN MENU            " << endl;
	cout << "================================" << endl;
	cout << "1. Create Account" << endl;
	cout << "2. View Account Details" << endl;
	cout << "3. View Transaction History" << endl;
	cout << "4. Perform Transaction" << endl;
	cout << "5. My Profile" << endl;
	cout << "6. Logout" << endl;
}

void runMenu(Customer* cust, Manager& manage) {
	bool running = true;

	while (running) {
		showMainMenu();
		int action = readInt("Enter choice: ");

		if (action == 1) {
			cust->createAcc();

		}
		else if (action == 2) {
			cout << "\n--- Your Accounts ---" << endl;
			showAccountList(cust);

			if (cust->getCusAccounts().empty()) continue;

			string accNum = readLine("Enter account number to view (or 0 to go back): ");
			if (accNum == "0") continue;

			bool found = false;
			for (Account& acc : cust->getCusAccounts()) {
				if (acc.getAccNum() == accNum) {
					cout << "\n--- Account Details ---" << endl;
					acc.displayAcc();
					found = true;
					break;
				}
			}
			if (!found) cout << "Account not found." << endl;

		}
		else if (action == 3) {
			cout << "\n--- Your Accounts ---" << endl;
			showAccountList(cust);

			if (cust->getCusAccounts().empty()) continue;

			string accNum = readLine("Enter account number to view transactions (or 0 to go back): ");
			if (accNum == "0") continue;

			bool found = false;
			for (Account& acc : cust->getCusAccounts()) {
				if (acc.getAccNum() == accNum) {
					acc.displayTrans();
					found = true;
					break;
				}
			}
			if (!found) cout << "Account not found." << endl;

		}
		else if (action == 4) {
			cout << "\n--- Perform Transaction ---" << endl;
			cout << "1. Deposit" << endl;
			cout << "2. Withdraw" << endl;
			cout << "3. Transfer (between my accounts)" << endl;
			cout << "4. Transfer (to another customer)" << endl;
			cout << "5. Back" << endl;
			int transChoice = readInt("Enter choice: ");

			if (transChoice == 1) {
				cout << "\nYour accounts:" << endl;
				showAccountList(cust);

				if (cust->getCusAccounts().empty()) continue;

				string accNum = readLine("Enter account number to deposit into: ");
				float amount = readFloat("Enter amount: ");

				if (amount <= 0) {
					cout << "Amount must be greater than zero." << endl;
				}
				else {
					bool done = false;
					for (Account& acc : cust->getCusAccounts()) {
						if (acc.getAccNum() == accNum) {
							acc.Deposit(amount);
							cout << "Deposit successful! New balance: " << acc.getAccBal() << endl;
							done = true;
							break;
						}
					}
					if (!done) cout << "Account not found." << endl;
				}

			}
			else if (transChoice == 2) {
				cout << "\nYour accounts:" << endl;
				showAccountList(cust);

				if (cust->getCusAccounts().empty()) continue;

				string accNum = readLine("Enter account number to withdraw from: ");
				float amount = readFloat("Enter amount: ");

				if (amount <= 0) {
					cout << "Amount must be greater than zero." << endl;
				}
				else {
					bool done = false;
					for (Account& acc : cust->getCusAccounts()) {
						if (acc.getAccNum() == accNum) {
							acc.Withdraw(amount);
							done = true;
							break;
						}
					}
					if (!done) cout << "Account not found." << endl;
				}

			}
			else if (transChoice == 3) {
				if (cust->getCusAccounts().size() < 2) {
					cout << "You need at least 2 accounts to transfer between them." << endl;
				}
				else {
					cout << "\nYour accounts:" << endl;
					showAccountList(cust);

					string from = readLine("Transfer FROM account number: ");
					string to = readLine("Transfer TO account number: ");
					float amount = readFloat("Amount: ");

					if (amount <= 0) {
						cout << "Amount must be greater than zero." << endl;
					}
					else {
						cust->transferSelf(amount, from, to);
					}
				}

			}
			else if (transChoice == 4) {
				cout << "\nYour accounts:" << endl;
				showAccountList(cust);

				if (cust->getCusAccounts().empty()) continue;

				string myAcc = readLine("Your account number to send FROM: ");
				int otherID = readInt("Recipient's Customer ID: ");

				if (otherID == cust->getCusID()) {
					cout << "To transfer between your own accounts, use option 3." << endl;
				}
				else {
					Customer* other = manage.getCustomer(otherID);
					if (other == nullptr) {
						cout << "Customer with ID " << otherID << " not found." << endl;
					}
					else {
						cout << "Sending to: " << other->getCusName() << endl;
						cout << "Their accounts:" << endl;
						showAccountList(other);

						string theirAcc = readLine("Their account number to send TO: ");
						float amount = readFloat("Amount: ");

						if (amount <= 0) {
							cout << "Amount must be greater than zero." << endl;
						}
						else {
							manage.transferOther(amount, cust->getCusID(), otherID, myAcc, theirAcc);
						}
					}
				}

			}
			else if (transChoice == 5) {
				continue;
			}
			else {
				cout << "Invalid choice." << endl;
			}

		}
		else if (action == 5) {
			cust->displayInfo();

		}
		else if (action == 6) {
			manage.saveAllToFile();
			cout << "\nLogged out. Goodbye, " << cust->getCusName() << "!" << endl;
			running = false;

		}
		else {
			cout << "Invalid option. Please try again." << endl;
		}
	}
}


int main() {

	Manager manage;
	manage.loadFromFile();

	cout << "==========================================" << endl;
	cout << "   Welcome to CodeAlpha Banking System" << endl;
	cout << "==========================================" << endl;
	cout << "1. New Customer" << endl;
	cout << "2. Existing Customer" << endl;
	int userType = readInt("Enter choice: ");

	if (userType == 1) {

		char wantAccount = readChar("\nWould you like to open an account with us? (Y/N): ");

		if (wantAccount == 'N' || wantAccount == 'n') {
			cout << "\nNo problem! We hope to see you soon. Goodbye!" << endl;
			return 0;
		}

		if (wantAccount != 'Y' && wantAccount != 'y') {
			cout << "Invalid input. Exiting." << endl;
			return 0;
		}

		cout << "\n--- New Customer Registration ---" << endl;
		string name = readLine("Full Name: ");
		int age = readInt("Age: ");
		char gender = readChar("Gender (M/F): ");
		string contact = readLine("Contact Number: ");

		if (name.empty()) {
			cout << "Name cannot be empty. Exiting." << endl;
			return 0;
		}
		if (age <= 0 || age > 120) {
			cout << "Invalid age. Exiting." << endl;
			return 0;
		}

		Customer newCust(name, contact, age, gender);
		manage.addCustomer(newCust);

		Customer* cust = manage.getCustomer(newCust.getCusID());

		cout << "\nRegistration successful!" << endl;
		cout << "Your Customer ID is: " << cust->getCusID() << endl;
		cout << "Please save this ID - you will need it to log in." << endl;

		cout << "\nLet's open your first account." << endl;
		cust->createAcc();

		manage.saveAllToFile();

		cout << "\n--- Identity Verification ---" << endl;
		int confirmID = readInt("Confirm your Customer ID: ");
		string confirmName = readLine("Confirm your Full Name: ");

		if (!manage.verifyCustomer(confirmID, confirmName)) {
			cout << "Verification failed. ID or name does not match. Exiting." << endl;
			return 0;
		}

		cout << "\nVerification successful! Welcome, " << cust->getCusName() << "." << endl;
		runMenu(cust, manage);

	}
	else if (userType == 2) {

		cout << "\n--- Customer Login ---" << endl;
		int loginID = readInt("Customer ID: ");
		string loginName = readLine("Full Name: ");

		if (!manage.verifyCustomer(loginID, loginName)) {
			cout << "\nLogin failed. Customer ID or name is incorrect." << endl;
			cout << "Please visit your nearest branch if you need help. Goodbye!" << endl;
			return 0;
		}

		Customer* cust = manage.getCustomer(loginID);
		cout << "\nLogin successful! Welcome back, " << cust->getCusName() << "." << endl;
		runMenu(cust, manage);

	}
	else {
		cout << "Invalid input. Please restart the program." << endl;
	}

	return 0;
}
