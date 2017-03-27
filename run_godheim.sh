if [ ! -d "Build" ]; then
    ./compile.sh
fi
cp Build/GodHeim IDJ
cd IDJ
./GodHeim
rm GodHeim
