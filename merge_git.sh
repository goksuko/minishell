echo "merge changes made in a branch into the main branch in Git"
git fetch origin
git checkout main
git merge goksu

echo "merge changes from main to the branch"
git fetch origin
git checkout my_goksu
git merge origin/main
echo "Resolve conflicts by accepting changes from main"
git checkout --theirs .
git add .
git commit
git push origin your-branch



git fetch --all
git rebase origin main
git push origin main