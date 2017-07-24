awk 'BEGIN{ n=ARGV[1] ; count=0 ; for(i=2;count<n;i++) { if(i > 2 && i%2 == 0) continue; j = 3 ;while(j <= i/2) { if(i%j == 0)break;j=j+2;} if(j > i/2){print i;count = count +1;}}}'  20
