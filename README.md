# libhide.so
Same concept as libprocesshider, but with the option to hide process by PID or process name

<h4>How to use libhide.so</h4>
Open libhide.c and choose either hide by PID or hide by name and comment out the other option with // at the beginning of the line.
Enter either the PID or process name you wish to hide.

<h4>To compile</h4>
sudo gcc -fPIC -shared -w libhide.c -o /usr/local/lib/libhide.so

<h4>Test it</h4>
LD_PRELOAD=/usr/local/lib/libhide.so ps -x | grep script.sh

<h4>Make it permanent.</h4>
root@localhost# echo /usr/local/lib/libhide.so >> /etc/ld.so.preload
<br><br>

Now, your process will be hidden!

# # 
