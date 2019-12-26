# linux_file_sys_tree_simulator
Linux File System Tree Simulator

```
ayushtiwari@Ayushs-MacBook-Air file_system % gcc *.c    
ayushtiwari@Ayushs-MacBook-Air file_system % ./a.out
user@machine / % menu
Command List
------------
mkdir pathname :make a new directory for a given pathname
rmdir pathname :remove the directory, if it is empty
cd [pathname]  :change CWD to pathname, or to / if no pathname
ls [pathname]  :list the directory contents of pathname or CWD
pwd            :print the (absolute) pathname of CWD
creat pathname :create a FILE node
rm pathname    :remove the FILE node
save filename  :save the currentfile system tree as a file
reload filename:construct afile system tree from a file
menu           :show a menu of valid commands
quit           :save thefile system tree, then terminate the program
user@machine / % mkdir X
user@machine / % cd X
user@machine /X/ % ls
user@machine /X/ % creat y
user@machine /X/ % ls
y	
user@machine /X/ %

```
