Input ".png" image should be given to preprocess.py via its path.
Then type in the following 3 commands:
python preprocess.py >> data.txt (*To excecute python file preprocess.py and writing its output to data.txt*)
sed -i 's/\[//g' data.txt
 (*To remove '[' from data.txt*)
sed -i 's/\]//g' data.txt (*To remove ']' from data.txt*)

Next type in command "make" to compile in terminal, an executable file called subtask1 is made.

Now for getting the top 5 probabilities of digits corresponding to the input image given to preprocess.py in "top5.txt" run the following command:
./subtask1 data.txt conv1.txt conv2.txt fc1.txt fc2.txt

This would output the corresponding top 5 probable digits with percentage probability in a file called "top5.txt".

We have included our latex report and pdf file as report.tex and report.pdf respectively with report.bib having the references.
