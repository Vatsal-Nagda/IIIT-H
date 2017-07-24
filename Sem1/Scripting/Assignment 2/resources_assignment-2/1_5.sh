awk 'BEGIN{ 
FS = "_" 
count=1
command = "sort -R SubmittedFiles.txt | cut -d '_' -f1"

while (command | getline teturn_numbert) {
  array[count] = teturn_numbert
  count=count +1
}
close(command)
}

END {
  ta[0] = "Prabhakar"
  ta[1] = "Sheshadri"
  ta[2] = "Viplav"
  ta[3] = "Akansha"
  ta[4] = "Deeksha"
  ta[5] = "Rambabu"
  ta[6] = "Harika"
  round=1
  for (turn_number = 1; turn_number <count; turn_number++)
  { print turn_number".  " ,array[turn_number]," - "ta[(turn_number-1)%7]

  if ((turn_number)%7==0)
    {
      print "----------------ROUND", round
      round++

    }
  }

  if ((turn_number)%7!=0)
  print "----------------ROUND", round
  

}

'<SubmittedFiles.txt



