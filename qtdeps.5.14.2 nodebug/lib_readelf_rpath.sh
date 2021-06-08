
#readelf -d bin/insane

libs=$(find lib/ -mindepth 1 ! -type l)

for f in $libs
do
	echo $f
	readelf -d $f | grep 'rpath\|runpath'
done
