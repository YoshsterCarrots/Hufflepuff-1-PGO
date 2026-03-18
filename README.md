# Hufflepuff-1-PGO
Data Scientist: Levi and Parker  
Tester: Matthew  
Instrumenter: Parker  
Pogo Stick: Levi  
  
We are taking a dataset of every trending YouTube video from early 2018 and writing a Markov-chain-adjacent program to generate new video titles (and tags?) that fit in with the rest

1. First, the program parses the csv files into an unordered_map indexed by video title that stores Video objects. The Video objects store the title, channel name, publish date, latest trending date, views, likes, dislikes, number of comments, the number of times the video trended, and the URL ID of the video. It adds all three csv files into one.
    * On top of storing the videos, it stores the tags on each video in its own unordered_map to keep track of which tags were the most popular overall during the time.  
2. After that, the unordered_maps for videos and tags are then offloaded into vectors to be sortable. These vectors are placed in a SortedCompilation object to ease the transition from map to vector.
    * In this object, the vectors are initialized as sorted by view count and number of times the tag appears by default, respectively.
3. Finally, the vectors are parsed to print out videos in lists of the top 100 of each category, with more detailed information being outputted to a .txt file. The top tags are also printed in their own category. 
