# UserEditor
Simple User Editor application - Software Design

Modules:

	MainWindow
    • readJSON()                        - parse JSON file and store data in QJsonArray
    • writeJSON()                       - parse QJsonArray and store data in JSON file
    • loadUsers()                       - load users from QJsonArray into QListWidget
    • addUser()                         - add new user to QJsonArray, refresh QListWidget
    • on_removePushButton_clicked()     - remove selected user from QJsonArray, refresh QListWidget
    • on_addPushButton_clicked()        - open AddUserDialog
    • on_usersListWidget_itemActivated()- show all info for user selected in QListWidget
    • onAddedUser()                     - slot for accept signal received from AddUserDialog

	AddUserDialog
    • on_buttonBox_accepted()           - parse input data and store in publicUser from QMainWindow

	User
    • User()                            - create User object from JsonObject
    • toJsonObject()                    - create JsonObject from User object

	Address
    • Address()                         - create Address object from JsonObject
    • toJsonObject()                    - creta JsonObject from Address object




Description:

After starting the application two functions are called - readJSON(), for parsing .json file, and loadUsers(), for displaying data in the GUI.

After parsing data from .json file, data is stored in QJsonArray.

loadUsers() function iterates through QJsonArray, create User objects, and inserts them into list users of type QList<Users>

After adding or removing user, QJsonArray is updated, and two functions are called:
	- writeJSON() function for writing data in .json file is called
	- loadUsers() function for displaying updated QJsonArray data in the GUI

By adding new user in AddUserDialog, accept signal is sent, and received by onAddedUser() slot in MainWindow. 
After receiving the signal, publicUser object of type User is added into QJsonArray using addUser() method.
  
  
