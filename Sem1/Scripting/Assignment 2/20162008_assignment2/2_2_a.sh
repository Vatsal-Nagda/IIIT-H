count=0
for index in *.tar.gz ; do
 
((count++))

echo -n "$i : "


lst_mdfy=`stat -c "%Y" $index`

dd_lne=$1

dd_lne1=`date -d "$dd_lne" +%s`

 if [ $dd_lne1 -lt $lst_mdfy ]
  then
      echo "REJECT";
 else
 
      echo "ACCEPT";
 fi
done

if [ $count -eq 0 ]
    then
    echo "REJECT";
fi