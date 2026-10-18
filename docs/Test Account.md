<h1 align="center" style="bold">Test Account</h1>

# Creation Process in VM
1. `git clone https://github.com/BruhCoVr/mysh.git`
2. `cd mysh`
3. `make mysh`
4. `sudo cp mysh /usr/local/bin`
5. `sudo nvim /etc/shells`\
Append `mysh` to the end of this file.\
`/usr/local/bin/mysh`
6. `sudo useradd --shell /usr/local/bin/mysh testuser` \
Set password to `testuser`, name to `TestUser`, and default for everything else. The `--shell` step removes the need for a `chsh` command after creating the new user. Does it all at once.
7. SSH testuser@10.65.255.<span style="color: orange">[YOURIP]</span> when logged into VPN w/ **testuser** as password and `mysh` is the running shell as expected

## Issues
1. Shell closes on CTRL+C - <span style="color: green">HANDLED</span>