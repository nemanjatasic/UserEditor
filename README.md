# UserEditor
Simple User Editor application - Software Design

Modules:

	MainWindow
    • readJSON()                        - parses JSON file and store data in QJsonArray
    • writeJSON()                       - parses QJsonArray and store data in JSON file
    • loadUsers()                       - loads users from QJsonArray into QListWidget
    • addUser()                         - adds new user to QJsonArray, refresh QListWidget
    • on_removePushButton_clicked()     - removes selected user from QJsonArray, refresh QListWidget
    • on_addPushButton_clicked()        - opens AddUserDialog
    • on_usersListWidget_itemActivated()- shows all info for user selected in QListWidget
    • onAddedUser()                     - slot for accept signal received from AddUserDialog
    • on_newFilePushButton_clicked()	- opens dialog for new .json file creating
    • on_openFilePushButton_clicked()	- opens dialog for selecting .json file on disk for opening
    • on_saveFilePushButton_clicked()	- saves the QJsonArray into .json file on disk

	AddUserDialog
    • on_buttonBox_accepted()           - parse input data and store in publicUser from QMainWindow

	User
    • User()                            - create User object from JsonObject
    • toJsonObject()                    - create JsonObject from User object

	Address
    • Address()                         - create Address object from JsonObject
    • toJsonObject()                    - creta JsonObject from Address object




Description:

After application user clicks the OPEN button and existing .json file is selected, two functions are called - readJSON(), for parsing .json file, and loadUsers(), for displaying data in the users list in main window.

After parsing data from .json file, data is stored in QJsonArray, which will be used for storing and modifying data during the application executon.

loadUsers() function iterates through QJsonArray, create User objects, and inserts them into list users of type QList<Users>.

NEW button in main window is used for creating new .json file (it's actually created after adding at least one user in the list) and for creating new user database. If some users is already loaded in user list, the list entries will be cleared.

After adding or removing user, QJsonArray is updated, and loadUsers() function is called.
	
By clicking on the ADD button AddUserDialog is opened for entering new user data. After accepting inputs User object is created and "accept" signal from AddUserDialog is sent to MainWindow to inform it that new user is created and needs to be added in QJsonArray. After receiving the signal by onAddedUser() slot in MainWindow, new user is added into QJsonArray using addUser() method.
	
By selecting some item (which is actually first and last name of user) in users list, all information about that user is displayed.
	
On SAVE button clicking QJsonArray is stored in .json file on disk.
  
  
