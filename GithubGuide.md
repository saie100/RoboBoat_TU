
## Initial GitHub setup

(1) Navigate to the folder in your terminal that you want the repository to be locally stored at. 

(2) Clone the repository to your computer:
'''
git clone [INSERT REPOSITORY ADDRESS]
'''

## Updating your local repository after changes have been made by others

(1) Navigate to the folder containing the repository in your terminal

(2) Pull updates from the GitHub
'''
git pull
'''

## Updating the repository with new files or changes you made to existing files

(1) Navigate to the folder containing the repository in your terminal

(2) Perform a 'git pull' command to update your local copy of the repository with changes that others may have made

(3) View your files that have been added/edited since your last 'push' that need to be updated in the repository
'''
git status
'''

(4a) Add your files that you want to commit (update) in the GitHub repository
'''
git add [INSERT FILES/DIRECTORIES HERE    MULTIPLE FILES/DIRECTORIES CAN BE SEPARATED BY SAPCES]
'''

(4b) Remove files from tracking that you never again wish to commit to the GitHub repository (optional - not always required)
'''
git rm [INSERT FILES/DIRECTORIES HERE    MULTIPLE FILES/DIRECTORIES CAN BE SEPARATED BY SAPCES]
'''

(5) Add a messge to the commit to let your team members know what you added/changed in the repository
'''
git commit -m "[ADD MESSAGE ABOUT THE FILE(S) BEING COMMITTED/UPDATED HERE]"
'''

(6) Push the changes to the repository and make your edits visible to your team members
'''
git push
'''

## Remove deleted files from tracking
'''
git add -u .
git commit -m "removing deleted files from tracking"
git push
'''
