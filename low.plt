set yrange[0.002380:0.002631]
set xrange[0:50000000]
set xtics 5000000

set terminal png size 1024,768
set output "/dev/null"

plot "low0.dat" using 1:4 title "Probability in number of trials(Xorshift)." w lp
replot "low1.dat" using 1:4 title "Probability in number of trials(MT)." w lp
replot 0.002543 title "1/393.216" 
replot 0.002530 title "1/395.202" 
replot 0.002517 title "1/397.188" 
replot 0.002505 title "1/399.174" 
replot 0.002492 title "1/401.160" 

set grid xtics
set output "low.png"
replot

reset
clear

set yrange[0.007033:0.008595]
set xrange[0:50000000]
set xtics 5000000
set grid xtics

set terminal png size 1024,768
set output "/dev/null"

plot "low0.dat" using 1:6 title "Probability in number of trials(Xorshift)." w lp
replot "low1.dat" using 1:6 title "Probability in number of trials(MT)." w lp
replot 0.007814 title "1/127.969" 
replot 0.007774 title "1/128.626" 
replot 0.007736 title "1/129.262" 
replot 0.007698 title "1/129.905" 
replot 0.007660 title "1/130.555" 

set grid xtics
set output "high.png"
replot


