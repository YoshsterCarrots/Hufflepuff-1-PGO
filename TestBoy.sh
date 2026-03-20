
for i in {1..3}
do
	Input="test_$i.csv"
	Expect="test_out_$i.txt"
	Out="compiledVideos.txt"
	./bin_gcov "$Input" > "$Out" 2>&1
 if diff -q "$Out" "$Expect" > /dev/null; then
	 echo "Test $i: passed :)"
 else
 	echo "Test $i: FAiled :("
 fi
done
