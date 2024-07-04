clear
make

echo "1"
./minishell "hello"
echo ""

echo "2"
./minishell "echo \\"
echo ""

echo "3"
./minishell "echo ;"
echo ""

echo "4"
./minishell "echo"
echo ""

echo "1st tester"
echo ""

echo "1st tester"
echo ""


echo "2nd tester"
cat ./test_files/infile_big | grep oi > result.txt
./minishell infile "cat ./test_files/infile_big" "grep oi" result2.txt
echo "difference:"
diff result.txt result2.txt
echo ""
echo "now memory check for bonus"
echo ""
valgrind ./minishell infile "cat ./test_files/infile_big" "grep oi" result2.txt
echo "2nd Done"
echo ""

echo "2nd tester without infile"
cat ./test_files/infile_big | grep oi > result.txt
./minishell "cat ./test_files/infile_big" "grep oi" result2.txt
echo "difference:"
diff result.txt result2.txt
echo ""
echo "now memory check for bonus"
echo ""
valgrind ./minishell "cat ./test_files/infile_big" "grep oi" result2.txt
echo "2nd Done"
echo ""