#!/bin/bash
scp -r hbidaman@arien.physics.uoguelph.ca:/helioshome/hbidaman/Geant/GRIFFIN/Edits/ .

git add .
# git add -u  (for only adding files already in the index)

echo 'Enter the commit message: '
read commitMessage

git commit -m "$commitMessage"

#git checkout -b <name of branch>  to create a new branch

echo 'Enter the name of the branch:'
read branch

git push origin $branch

#read
