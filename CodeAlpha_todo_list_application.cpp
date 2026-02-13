#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Task {

private:
	int taskID;
	string taskDes;
	string taskCat;
	bool taskStat;

public:

	Task(int taskID, string taskDes, string taskCat, bool taskStat) {
		this->taskID = taskID;
		this->taskDes = taskDes;
		this->taskCat = taskCat;
		this->taskStat = taskStat;
	}

	int getTaskid() {
		return taskID; 
	}
	string getTaskDes() {
		return taskDes;
	}
	bool getTaskStat() {
		return taskStat;
	}
	string getTaskCat() {
		return taskCat;
	}

	void setTaskDes(string newDes) {
		taskDes = newDes;
	}
	void setTaskStat(bool newStat) {
		taskStat = newStat;
	}

	void taskInfo() {
		cout << "Task ID: " << taskID << endl;
		cout << "Task Category: " << taskCat << endl;
		cout << "Task Description: " << taskDes << endl;
		if (taskStat) {
			cout << "Task State: Completed" << endl;
		}
		else {
			cout << "Task State: Pending" << endl;
		}
	}

};

class TaskManager {

private: 
	vector<Task> tasks;

	void saveTaskToCSV(int taskID, string category, string describe, bool completed) {
		ofstream csvFile;
		csvFile.open("TaskFile.csv", ios::app);

		if (csvFile.is_open()) {
			csvFile << taskID << "|"
				<< category << "|"
				<< describe << "|"
				<< (completed ? "true" : "false") << endl;
			csvFile.close();
		}
	}

	void updateTaskInCSV(int taskID, string newDesc, bool newStatus) {
		ifstream inputFile("TaskFile.csv");
		ofstream tempFile("temp.csv");

		string line;
		getline(inputFile, line);
		tempFile << line << endl;

		while (getline(inputFile, line)) {
			stringstream ss(line);
			string idStr, cat, desc, status;

			getline(ss, idStr, '|');
			getline(ss, cat, '|');
			getline(ss, desc, '|');
			getline(ss, status, '|');

			if (stoi(idStr) == taskID) {

				tempFile << idStr << "|" << cat << "|" << newDesc << "|" << (newStatus ? "true" : "false") << endl;
			}
			else {

				tempFile << line << endl;
			}
		}

		inputFile.close();
		tempFile.close();

		if (remove("TaskFile.csv") != 0) {
			cout << "Error deleting original file!" << endl;
			return;
		}

		if (rename("temp.csv", "TaskFile.csv") != 0) {
			cout << "Error renaming temp file!" << endl;
			return;
		}

	}

	void deleteTaskFromCSV(int taskID) {
		ifstream inputFile("TaskFile.csv");
		ofstream tempFile("temp.csv");

		string line;
		getline(inputFile, line);
		tempFile << line << endl;

		while (getline(inputFile, line)) {
			stringstream ss(line);
			string idStr;
			getline(ss, idStr, '|');


			if (stoi(idStr) != taskID) {
				tempFile << line << endl;
			}
		}

		inputFile.close();
		tempFile.close();

		if (remove("TaskFile.csv") != 0) {
			cout << "Error deleting original file!" << endl;
			return;
		}

		if (rename("temp.csv", "TaskFile.csv") != 0) {
			cout << "Error renaming temp file!" << endl;
			return;
		}

		for (int i = 0; i < tasks.size(); i++) {
			if (tasks[i].getTaskid() == taskID) {
				tasks.erase(tasks.begin() + i);
				break;
			}
		}
	}

public:
	
	vector<Task>& getTasks() {
		return tasks;
	}

	void addSingleTask(Task obj) {
		tasks.push_back(obj);
		saveTaskToCSV(obj.getTaskid(), obj.getTaskCat(), obj.getTaskDes(), obj.getTaskStat());
	}

	void addAllTask(Task obj) {
		tasks.push_back(obj);
	}

	void showTask(bool status, string category) {
		bool found = false;
		for (Task& obj : tasks) {
			if (obj.getTaskStat() == status && obj.getTaskCat() == category) {
				obj.taskInfo();
				cout << "\n";
				found = true;
			}
			else if (obj.getTaskStat() == status && category == "All") {
				obj.taskInfo();
				cout << "\n";
				found = true;
			}
		}
		if (!found) {
			cout << "No " << (status ? "Completed " : "Pending ") << category << " Tasks Found." << endl;
		}
	}

	void updateTask(int taskID, string newDesc, bool newStatus) {
		for (Task& obj : tasks) {
			if (obj.getTaskid() == taskID) {
				obj.setTaskDes(newDesc);
				obj.setTaskStat(newStatus);
				break;
			}
		}
		updateTaskInCSV(taskID, newDesc, newStatus);
	}

	void deleteTask(int taskID) {
		for (int i = 0; i < tasks.size(); i++) {
			if (tasks[i].getTaskid() == taskID) {
				tasks.erase(tasks.begin() + i);
				break;
			}
		}
		deleteTaskFromCSV(taskID);
	}

	void delTaskFile() {

		if (remove("TaskFile.csv") != 0) {
			cout << "Error deleting To-Do List!" << endl;
			return;
		}
		else {
			cout << "Successfully deleted To-Do List" << endl;
		}

	}

};

void loadTasksFromCSV(TaskManager& manager) {

	ifstream csvFile("TaskFile.csv");
	string line;

	getline(csvFile, line);

	while (getline(csvFile, line)) {
		stringstream ss(line);
		string taskIDStr, category, describe, statusStr;

		getline(ss, taskIDStr, '|');
		getline(ss, category, '|');
		getline(ss, describe, '|');
		getline(ss, statusStr, '|');

		int taskID = stoi(taskIDStr);
		bool completed = (statusStr == "true");

		Task task(taskID, describe, category, completed);
		manager.addAllTask(task);
	}
	csvFile.close();

}

bool fileExists(const string& filename) {
	ifstream file(filename);
	return file.good();
}

int main() {

	TaskManager tasks;

	if (fileExists("TaskFile.csv")) {
		loadTasksFromCSV(tasks);
	}
	else {
		ofstream file("TaskFile.csv");
		file << "TaskID|Category|Description|Status" << endl;
		file.close();
	}
	cout << "*********************************" << endl;
	cout << "***** Welcome to TO-DO List *****" << endl;
	cout << "*********************************" << endl;
	cout << endl;
	bool cond = true;
	while (cond) {
		int opt;
		cout << "1.Add Task " << endl << "2.View Task" << endl << "3.Update Task" << endl << "4.Delete Task" << endl 
			 << "5.Delete List" << endl << "6.Exit" << endl;
		cout << "Select an operation: ";
		cin >> opt;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input! Try Again!" << endl;
			continue;
		}
		switch (opt) {
		case 1:
		{
			cout << endl;
			vector<Task> alltask = tasks.getTasks();
			int taskID;
			bool catCond = true, statCond = true;
			string taskCat;
			int catOpt; 
			string taskDes;
			int taskStatusopt;
			string taskStatus;

			if (alltask.size() == 0) {
				taskID = 1;
			}
			else {
				taskID = alltask.back().getTaskid() + 1;
			}

			while (catCond) {
				cout << "Enter the Category (1.Personal 2.Work 3.Education): ";
				cin >> catOpt;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input! Try Again!" << endl;
					continue;
				}
				switch (catOpt) {
				case 1:
					taskCat = "Personal";
					catCond = false;
					break;
				case 2:
					taskCat = "Work";
					catCond = false;
					break;
				case 3:
					taskCat = "Education";
					catCond = false;
					break;
				default:
					cout << "Invalid Input! Try Again!" << endl;
				}
			}
			cout << "Enter the Description: ";
			cin.ignore();
			getline(cin, taskDes);
			while (statCond) {
				cout << "Enter the Status (1.Pending 2.Completed): ";
				cin >> taskStatusopt;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input! Try Again!" << endl;
					continue;
				}
				else {
					break;
				}
			}
			if (taskStatusopt == 1) {
				taskStatus = "Pending";
			}
			else {
				taskStatus = "Completed";
			}

			if (taskStatus == "Pending") {
				Task obj(taskID, taskDes, taskCat, false);
				tasks.addSingleTask(obj);
			}
			else if (taskStatus == "Completed") {
				Task obj(taskID, taskDes, taskCat, true);
				tasks.addSingleTask(obj);
			}
			else {
				cout << "Invalid Status!";
			}
			cout << endl;
			break;
		}
		case 2: {
			int view, catOpt, ans;
			string cat;
			cout << endl;
			cout << "1.View Pending Task 2.View Completed Task" << endl;
			cout << "Select an operation: ";
			cin >> view;
			cout << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Input!" << endl;
				continue;
			}
			while (true) {
				cout << "1.Personal 2.Work 3.Education 4.All" << endl;
				cout << "Select a Category: ";
				cin >> catOpt;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input! Try Again!" << endl;
					continue;
				}
				switch (catOpt) {
				case 1: {
					cat = "Personal";
					break;
				}
				case 2: {
					cat = "Work";
					break;
				}
				case 3: {
					cat = "Education";
					break;
				}
				case 4: {
					cat = "All";
					break;
				}
				default:
					cout << "Invalid Input!" << endl;
				}
				cout << endl;
				switch (view) {
				case 1:
					tasks.showTask(false, cat);
					break;
				case 2:
					tasks.showTask(true, cat);
					break;
				default:
					cout << "Invalid Operation!";
				}
				cout << "Do you want to check other category?" << endl;
				cout << "1.Yes 2.No : ";
				cin >> ans;
				cout << endl;
				if (ans == 2) {
					break;
				}
				else if (ans != 1) {
					cout << "Invalid Input!" << endl;
					break;
				}
			}
			cout << endl;
			break;
		}
		case 3: {
			int ID, choice;
			bool found = false;
			cout << endl;
			cout << "1.Update Desription 2.Update Status" << endl;
			cout << "Select an operation: ";
			cin >> choice;
			while (true) {
				cout << "Enter the Task ID: ";
				cin >> ID;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input! Try Again!" << endl;
				}
				else {
					break;
				}
			}
			

			for (Task& obj : tasks.getTasks()) {
				if (obj.getTaskid() == ID) {
					found = true;
					switch (choice) {
					case 1:
					{
						string newDes;
						cout << "Enter the new description: ";
						cin.ignore();
						getline(cin, newDes);
						tasks.updateTask(obj.getTaskid(), newDes, obj.getTaskStat());
						obj.setTaskDes(newDes);
						cout << endl;

						break;
					}
					case 2: {
						int statusOpt;
						bool newStat;
						while (true) {
							cout << "Enter the new status (1.Pending 2.Completed): ";
							cin >> statusOpt;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1000, '\n');
								cout << "Invalid Input! Try Again!" << endl;
								continue;
							}
							if (statusOpt == 1) {
								newStat = false;
								break;
							}
							else if (statusOpt == 2) {
								newStat = true;
								break;
							}
							else {
								cout << "Invalid Status! Try Again!" << endl;
							}
						}
						tasks.updateTask(obj.getTaskid(), obj.getTaskDes(), newStat);
						obj.setTaskStat(newStat);
						cout << endl;
						break;
					}
					default:
						cout << "Invalid Operation!";
					}
					break;
				}
			}
			if (!found) {
				cout << "Task not found!\n" << endl;
			}
			break;
		}
		case 4: {
			int ID;
			bool found = false;
			while (true) {
				cout << "\nEnter the Task ID: ";
				cin >> ID;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Input! Try Again!" << endl;
				}
				else {
					break;
				}
			}

			for (Task& obj : tasks.getTasks()) {
				if (obj.getTaskid() == ID) {
					found = true;
					break;
				}
			}

			if (found) {
				tasks.deleteTask(ID);
				cout << "Task deleted successfully!" << endl;
			}
			else {
				cout << "Task not found!" << endl;
			}
			cout << endl;
			break;
		}
		case 5: {
			int opt;
			cout << "\nDeleting To-Do List! Are you sure? " << endl;
			cout << "1.Yes 2.No:";
			cin >> opt;
			if (opt == 1) {
				tasks.delTaskFile();
				tasks.getTasks().clear();
			}
			else if (opt != 2) {
				cout << "Invalid Input!" << endl;
			}
			cout << endl;
			break;
		}
		case 6: {
			cond = false;
			break;
		}
		default:
			cout << "Invalid Operation! Try Again!" << endl;
		}
	}
}