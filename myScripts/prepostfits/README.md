# 1. Copy the data

Copy and paste the minitree containing the data within this directory. 

# 2. Run preparePrepostfits.C

Run the code to produce as output different directories containing the rootfiles that can be read by PlotterPrepostfits.C (one directory/mass point).
Then, in order to have the correct files to give to the Plotter, just copy and paste in the terminal the content of the file merge.txt (this will for example merge all the different prefit processes into a single one, 18_prefit.root).

# 3. Getting ready for the Plotter

Then, in order to have the correct files to give to the	Plotter, just copy and paste the file merge.txt in a terminal session (this will for example merge all the dif\
ferent prefit processes	into a single one, 18_prefit.root), and do the same with prepareForPlotter.txt (which will gather both the pre- and postfits rootfiles into the same directory, for the plotter to consider them both in the same time).

# 4. Run the plotter

Copy and paste in the terminal the content of the plotter.txt file to run the plotter for all the different mass points, or run them one by one using the following command:
root -l -b -q "PlotterPrepostfits.C(\"hist\", \"ttDM0001scalar00010\")"

# 5. Copy the plots to the web

Copy and paste the content of copy.txt (within the correct www directory!) to move all the plots and rename them correctly.