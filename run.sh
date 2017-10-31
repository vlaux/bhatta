for file in partials/*
do
	echo "running $file"
	./bhatta $file
done 
