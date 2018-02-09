#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

using namespace std;

int main() {
    vector<string> supported_commands = {"echo", "cd", "ls", "pwd", "cp", "cat", "rm", "exit"};
    char pwd_chara[1024];
    getcwd(pwd_chara, sizeof(pwd_chara));
    string pwd(pwd_chara);
    while (true) {
        cout << "$ ";
        string command_string;
        getline(cin, command_string);
        istringstream command_string_stream(command_string);
        string command;
        command_string_stream >> command;
        auto index = find(supported_commands.begin(), supported_commands.end(), command);
        if (index != supported_commands.end()) {
            if (command == "echo") {
                command_string_stream >> cout.rdbuf();
                cout << '\n';
            } else if (command == "pwd") {
                cout << pwd << '\n';
            } else if (command == "cd") {
                string directory_name;
                command_string_stream >> ws;
                getline(command_string_stream, directory_name);
                if (directory_name[0] == '.' && directory_name[1] == '/')
                    directory_name = directory_name.substr(2);
                if (directory_name == "..") {
                    if (pwd.length() > 1 && pwd.find_last_of('/') != string::npos) {
                        pwd = pwd.substr(0, pwd.find_last_of('/') + 1);
                        if (pwd.length() > 1)
                            pwd = pwd.substr(0, pwd.length() - 1);
                    }
                } else if (opendir((pwd + "/" + directory_name).c_str())) {
                    pwd += "/" + directory_name;
                } else if (ENOENT == errno) {
                    cout << pwd + "/" + directory_name << ": No such Directory found!" << '\n';
                }
            } else if (command == "ls") {
                dirent *d;
                DIR *temp_directory;
                temp_directory = opendir(pwd.c_str());
                while (d = readdir(temp_directory)) {
                    cout << d->d_name << '\n';
                }
            } else if (command == "cp") {
                string ifilename; command_string_stream >> ifilename;
                string ofilename; command_string_stream >> ofilename;
                int in_fd = open((pwd + "/" + ifilename).c_str(), O_RDONLY);
                if (in_fd < 0) {
                    cout << pwd + "/" + ifilename << ": No such file found!\n";
                    continue;
                }
                int out_fd = open((pwd + "/" + ofilename).c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
                if (out_fd < 0) {
                    cout << pwd + "/" + ofilename << ": Unable to create file!\n";
                    continue;
                }
                char rdbuffer[8192];

                while (true) {
                    ssize_t result = read(in_fd, &rdbuffer[0], sizeof(rdbuffer));
                    if (!result) break;
                    if (result <= 0) {
                        cout << pwd + "/" + ifilename << ": File reading failed!\n";
                        break;
                    }
                    if (write(out_fd, &rdbuffer[0], result) != result) {
                        cout << pwd + "/" + ofilename << ": File writing failed!\n";
                        break;
                    }
                }
            } else if (command == "cat") {
                string ifilename; command_string_stream >> ifilename;
                int in_fd = open((pwd + "/" + ifilename).c_str(), O_RDONLY);
                if (in_fd < 0) {
                    cout << pwd + "/" + ifilename << ": No such file found!\n";
                    continue;
                }
                char rdbuffer[8192];

                while (true) {
                    ssize_t result = read(in_fd, &rdbuffer[0], sizeof(rdbuffer));
                    if (!result) break;
                    if (result <= 0) {
                        cout << pwd + "/" + ifilename << ": File reading failed!\n";
                        break;
                    }
                    cout << rdbuffer;
                }
                cout << '\n';
            } else if (command == "rm") {
                string ifilename; command_string_stream >> ifilename;
                if (unlink((pwd + "/" + ifilename).c_str()) < 0)
                    cout << pwd + "/" + ifilename << ": Failed removing file!\n";
            } else if (command == "exit") {
                break;
            }
        } else {
            cout << command << ": Command not found!\n";
        }
    }
    return 0;
}