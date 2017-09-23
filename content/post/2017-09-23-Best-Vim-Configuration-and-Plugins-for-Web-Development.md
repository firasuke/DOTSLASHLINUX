+++
title = "Best Vim Configuration and Plug-ins for Web Development"
slug = "best vim configuration and plugins for web development"
nick = "vim"
date = "2017-09-23"
author = "Firas Khalil Khana"
imgsrc = "/img/vim.png"
imgalt = "vim"
+++
I've been constantly switching between text editors. At first I started using nano for terminal/tty purposes and Leafpad for a GUI editor. They were pretty neat for quick basic editing (especially nano), but they were never suitable for programming and writing articles.
<br/>
<br/>
I then moved to Geany, which was wonderful. It had everything I needed, a nice color scheme (monokai from geany-themes on github), and was super fast, but it was only suitable for C/C++ programming and it wasn't meant to be used for web development.
<br/>
<br/>
Throughout the way I've gave Vim like 50 chances to prove it was worth it, but it failed me every time. I then found out about Bluefish Editor, and I hated it the moment I started using it. It was fast, and had a lot of features, but its editor lacked a lot of stuff I thought were important, plus using it just felt weird (with all do respect to all Bluefish developers, you're doing a great job, it's just that it wasn't suited for a user like me).
<br/>
<br/>
A couple of months passed, and I was switching constantly between Geany, nano and Leafpad until I found out about Atom from GitHub and boy it was awesome! Fired up that terminal emulator and a whopping 600mb package was waiting to be built from source, now isn't that fantastic... Atom needed electron, the base Javascript framework that it was build on, and compiling a package this big from source isn't something easy (all the Gentoo boys and girls who tried to emerge chromium will be nodding their heads in approval... yes I can feel you...) as you never know if it'll work as expected or not, or if you've missed a feature or not but I did it, and couldn't be any happier.
<br/>
<br/>
I then wrote the first version of this website in Atom, things were really easy. Instant preview in an integrated web browser, auto completion, amazing color scheme, snippets for everything and a ton of features. But then as I added more and more plug-ins Atom was growing into a bloated mess of Javascript code that I couldn't withstand. I mean every time I started it, it took at least 10 seconds to get fully working and I hated that. It also (although rarely) crashed on me in several occasions which made me finally make the decision of switching to Vim.
<br/>
<br/>
I emerged Vim, and at first it was the worst thing I've tried on GNU/Linux so far... I said to myself "I wonder if I'm mistaken, I mean look at all those power Vim users out there and how quickly they finish tasks that take at least a couple of minutes on other editors in a second or two". I acknowledged that the problem was with me and not with Vim. And I forced myself into learning Vim and I'm glad I did that.
<br/>
<br/>
I coded the website from scratch this time using Vim. Day after day, I was getting better and faster. I stopped using nano and Leafpad. The Vim editor, that I thought was the worst thing to ever exist on a GNU/Linux operating system, was slowly turning into the best thing that I've ever used. It can be launched in any terminal emulator/tty. It starts in a mere second or two with all plug-ins fully loaded. It has a ton of plug-ins to choose from and a strong community behind it.
<br/>
<br/>
It took me 3 months to get used to Vim and its key bindings, and I now highly recommend it to anyone who wants a light productive text editor.
<br/>
<br/>
So yes the website you're viewing right now was proudly coded using Vim, and all of my articles were rewritten using Vim. It was until recently that a couple of DOTSLASHLINUX followers requested that I post a guide on how to configure Vim, and what plug-ins I use alongside it since they thought that the pictures that showcased Vim the most were the coolest ones, and here I'm writing an article for DOTSLASHLINUX's loyal viewers.
<br/>
<br/>
Enough talking, let's get this thing started!
<br/>
<br/>
<hr/>
<h3>1- Installation</h3>
<br/>
Gentoo Linux:
```properties
emerge --sync && emerge -av app-editors/vim
```
<br/>
Void Linux:
```properties
xbps-install -Su && xbps-install -S vim
```
<br/>
Arch Linux:
```properties
pacman -Syu vim
```
<br/>
<hr/>
<h3>2- Configuration</h3>
As most programs in GNU/Linux, the configuration file found in /etc <mark>/etc/vim/vimrc</mark> is intended for system-wide or global settings (meaning it'll be applied to all users including your root user), and the recommended configuration file that you should be editing is <mark>/.vimrc</mark>.
<br/>
<br/>
So fire up your favorite editor (... Wait a second, we're going to use Vim to configure Vim... makes sense...), and run:
```properties
vim /.vimrc
```
<br/>
And use this configuration file:
```vim,line-numbers
" <-- this double quote indicates a vimrc comment

" Change Vim's default color scheme to apprentice which is
" a dark, low contrast and slate color scheme that's undistracting
" and suitable for coding as it reduces eye strain
" (emerge app-vim/colorschemes)
colorscheme apprentice

" This is extremely useful for indenation purposes
" of several filetypes used in web development
" as you can simply press gg=G for auto indentation
filetype plugin indent on

" This will show line numbers
set number

" We'll combine normal line numbers with relative
" line numbers to make it easier to move between
" multiple lines
set relativenumber

" This will enable Vim's syntax highlighting
syntax on

" This will enable Vim's spell checking feature
" for the English language (emerge -av vim-spell-en)
set spell spelllang=en

" We'll be using this option to modify files directly
" inside NERDTree inside Vim, without having to exit Vim
set modifiable

" This will highlight the current line your cursor is at
set cursorline

" This will highlight the current column your cursor is at
" and it'll make it much easier to determine your closing tags
" (along with matchtagalways) when code is properly indented
set cursorcolumn

" This will enable the usage of your mouse inside Vim in
" terminal emulators that support it (gpm)
set mouse=a

" This option speeds up macro execution in Vim
" Some users may rarely experience glitches with this option
" enabled
set lazyredraw

" This enabled 256-color support in Vim, which is needed
" by many color schemes
set t_Co=256

" This will make Vim start searching the moment you start
" typing the first letter of your search keyword
set incsearch

" This will make Vim highlight all search results that
" matched the search keyword
set hlsearch

" This will make tabs 2 spaces wide
set tabstop=2

" This is needed to tree tabs as multiple spaces
set shiftwidth=2

" This option will enable you to enter a real Tab character
" by pressing Ctrl-V<Tab>
set expandtab

" This will enable NERDTree to show hidden files
let NERDTreeShowHidden=1
```
<br/>
<hr/>
<h3>3- Plug-ins</h3>
I generally like to manually install my plug-ins. Although, many would recommend against that not because it's hard but because things may get messy sometimes, but it suits me well.
<br/>
<br/>
If you'd like to use a plug-in manager then I highly recommend <a href="https://github.com/tpope/vim-pathogen" target="_blank">pathogen.vim</a>.
<br/>
<br/>
You have mainly 2 sources for Vim plug-ins. The first being your distribution's repositories and the second being GitHub. Most of the time, your distribution's repositories will have the plug-in you're looking for unless it was extremely new or not popular.
<br/>
<br/>
There are a couple of downsides for installing plug-ins directly from GitHub. The first is the manual management and installation of these plug-ins and the second is updating them as your distribution's package manager won't detect these user installed plug-ins.
<br/>
<br/>
I'd also like to recommend this awesome website <a href="https://vimawesome.com/" target="_blank">VimAwesome</a> that's considered a Vim plug-in heaven for all Vim users.
<br/>
<br/>
Before listing these plug-ins, I'd like you to take a look at <mark>/usr/share/vim</mark>, and examine the contents of the directories listed inside. In my system, here's an output of what's inside:
```bash
ls -lh /usr/share/vim
```
```properties
total 4.0K
drwxr-xr-x 18 root root 4.0K Sep 16 18:49 vim80
drwxr-xr-x 14 root root  191 Sep 22 13:49 vimfiles
```
<br/>
Now focus on vimfiles, as plug-ins will be installed there:
```bash
ls -lh /usr/share/vim/vimfiles
```
```properties
total 12K
drwxr-xr-x  10 root root  300 Sep 22 22:05 autoload
drwxr-xr-x   2 root root  324 Sep 22 13:58 doc
drwxr-xr-x   2 root root   97 Sep 21 11:20 ftdetect
drwxr-xr-x   2 root root 4.0K Sep  9 12:15 ftplugin
drwxr-xr-x   2 root root   84 Sep 21 11:20 indent
drwxr-xr-x   3 root root   22 Aug 22 13:53 lib
drwxr-xr-x   2 root root   79 Aug 22 13:56 nerdtree_plugin
drwxr-xr-x   3 root root  319 Sep 22 13:58 plugin
drwxr-xr-x   3 root root  114 Aug 23 14:29 python
drwxr-xr-x   2 root root  128 Sep 22 12:37 spell
drwxr-xr-x   2 root root 4.0K Sep 22 13:51 syntax
drwxr-xr-x 107 root root 4.0K Sep 22 13:49 syntax_checkers
```
<br/>
The reason behind doing this is to get you familiar to the structure of this directory. In most cases, you'll be manually copying the scattered contents of a plug-in downloaded from GitHub to some directories located in vimfiles. Don't worry I'll be showing you an example of a plug-in manually installed from GitHub.
<br/>
<br/>
With that being said, let's get started!
<br/>
<br/>
<hr/>
<h3>3.1- <a href="https://github.com/scrooloose/nerdtree" target="_blank">The NERDTree</a></h3>
This shouldn't surprise anybody. The NERDTree, the famous tree explorer plug-in for Vim, used on almost all Vim setups. You can get a good understanding of where you are and what file are you currently editing in Vim. Plus, it gives Vim that IDE feel.
<br/>
<br/>
To install The NERDTree on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/nerdtree app-vim/nerdtree-tabs
```
<br/>
To toggle The NERDTree inside Vim, simply run:
```none
:NERDTree
```
<br/>
To move from your editor to The NERDTree, hit <mark>Ctrl + w</mark> then <mark>&larr;</mark> (the left arrow key).
<br/>
<br/>
To get back to the editor hit <mark>Ctrl + w</mark> then <mark>&rarr;</mark> (the right arrow key).
<br/>
<br/>
To show hidden files using The NERDTree, add this line to your <mark>/.vimrc</mark>:
```vim
...
let NERDTreeShowHidden=1
...
```
<br/>
<hr/>
<h3>3.2- <a href="https://github.com/itchyny/lightline.vim" target="_blank">lightline.vim</a></h3>
This is also another popular Vim plugin. lightline.vim is an extremely lightweight status bar for Vim. It shows information about your current file, line number, column number, encoding type, file type, and a ton of other useful information.
<br/>
<br/>
To install lightline.vim on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/lightline
```
<br/>
lightline should automatically toggle itself when you edit a file using Vim.
<br/>
<hr/>
<h3>3.3- <a href="https://github.com/severin-lemaignan/vim-minimap" target="_blank">vim-minimap</a></h3>
Yup, there's even a minimap plug-in for Vim. Isn't this just awesome! This plug-in isn't available in the official repositories of many distributions and you'll have to get it from GitHub.
<br/>
<br/>
Simply run:
```properties
cd ~ && git clone https://github.com/severin-lemaignan/vim-minimap
```
<br/>
then:
```properties
cd ~/vim-minimap/
```
<br/>
Now let's see what's in this directory:
```properties
ls -lh ~/vim-minimap/
```
```properties
total 112K
drwxr-xr-x 3 firas firas   59 Sep 17 00:49 autoload
-rw-r--r-- 1 firas firas 1.1K Sep 17 00:49 LICENSE
-rw-r--r-- 1 firas firas 104K Sep 17 00:49 minimap.png
drwxr-xr-x 2 firas firas   25 Sep 17 00:49 plugin
-rw-r--r-- 1 firas firas 2.2K Sep 17 00:49 README.md
```
<br/>
So we have an autoload directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/autoload</mark>, we also have a plugin directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/plugin</mark>. We also have a LICENSE file, a minimap.png image, and a README.md which won't be needed for this plug-in to work.
<br/>
<br/>
Now run:
```properties
cp -rav ~/vim-minimap/autoload/ /usr/share/vim/vimfiles/autoload/
cp -rav ~/vim-minimap/plugin /usr/share/vim/vimfiles/plugin/
```
<br/>
Start vim and toggle the minimap by running:
```none
:Minimap
```
<br/>
This is how you manually install a Vim plug-in, easy isn't it?
<hr/>
<h3>3.4- <a href="https://github.com/ctrlpvim/ctrlp.vim" target="_blank">ctrlp.vim</a></h3>
ctrlp.vim the famous fuzzy file finder for Vim. It's incredibly fast and allows you to quickly access any file wherever it is on your system.
<br/>
<br/>
To install ctrlp.vim on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/ctrlp
```
<br/>
As the name implies, hit <mark>Ctrl + p</mark> and start typing. It'll start searching in the current directory the moment you type.
<br/>
<br/>
To go up the directory tree by one level, simply type <mark>..</mark> (double dots).
<br/>
<br/>
<hr/>
<h3>3.5- <a href="https://github.com/garbas/vim-snipmate" target="_blank">snipMate</a></h3>
And no web development setup would be complete without snippets.
<br/>
<br/>
To install snipMate on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/snipmate
```
<br/>
<hr/>
<h3>3.6- <a href="https://github.com/tpope/vim-surround" target="_blank">surround.vim</a></h3>rom the creator of the famous Vim plug-in manager <a href="https://github.com/tpope/vim-pathogen" target="_blank">pathogen.vim</a>, this plug-in is extremely useful to quickly surround your text/code with tags of different types.
<br/>
<br/>
To install surround.vim on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/surround
```
<br/>
<hr/>
<h3>3.7- <a href="https://github.com/mattn/emmet-vim" target="_blank">emmet-vim</a></h3>
Whenever we hear the term web development, we see emmet popping up and you guessed it, there's an emmet plug-in for Vim. For those who don't know, emmet expands on abbreviations and saves you a lot of time. 
<br/>
<br/>
To install emmet-vim on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/emmet
```
<br/>
To use emmet, do a visual select <mark>Shift+v</mark> then hit <mark>Ctrl + y + ,</mark> (don't forget the comma), and you'll get a <mark>Tag:</mark> prompt, you can now type <mark>ul>li&ast;</mark> and it'll add unordered list tags and list item tags to all the selected lines and close them for you! How convenient!
<br/>
<br/>
<hr/>
<h3>3.8- <a href="https://github.com/valloric/matchtagalways" target="_blank">MatchTagAlways</a></h3>
This plug-in will make your life easier, and it'll save you a lot of eye strain and brain power trying to figure out where on earth did the closing tag disappear, as it highlights both opening and closing tags for several file types. This plug-in isn't available in the official repositories of many distributions and you'll have to get it from GitHub.
<br/>
<br/>
Simply run:
```properties
cd ~ && git clone https://github.com/valloric/matchtagalways
```
<br/>
then:
```properties
cd ~/matchtagalways/
```
<br/>
Now let's see what's in this directory:
```properties
ls -lh ~/matchtagalways/
```
```properties
total 48K
drwxr-xr-x 2 firas firas   32 Aug 23 13:55 autoload
-rw-r--r-- 1 firas firas  35K Aug 23 13:55 COPYING.txt
drwxr-xr-x 2 firas firas   32 Aug 23 13:55 doc
drwxr-xr-x 2 firas firas   32 Aug 23 13:55 plugin
drwxr-xr-x 3 firas firas   75 Aug 23 13:55 python
-rw-r--r-- 1 firas firas 5.5K Aug 23 13:55 README.md
-rw-r--r-- 1 firas firas 2.8K Aug 23 13:55 test.html
```
<br/>
So we have an autoload directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/autoload</mark>, we also have a doc directory which needs it contents to be copied to <mark>/usr/share/vim/vimfiles/doc/</mark> and a plugin directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/plugin</mark>.
<br/>
<br/>
There's also this python directory, that needs its content to be copied to <mark>/usr/share/vim/vimfiles/python</mark> (create this directory if it doesn't exist). We also have a COPYING.txt file, a README.md file, and a test.html file which won't be needed for this plug-in to work.
<br/>
<br/>
Now run:
```properties
cp -rav ~/matchtagalways/autoload/ /usr/share/vim/vimfiles/autoload/
cp -rav ~/matchtagalways/doc/ /usr/share/vim/vimfiles/doc/
cp -rav ~/matchtagalways/plugin/ /usr/share/vim/vimfiles/plugin/
cp -rav ~/matchtagalways/python/ /usr/share/vim/vimfiles/python/
```
<br/>
matchtagalways should be automatically working whenever you edit a file type that makes use of opening and closing tags.
<br/>
<br/>
<hr/>
<h3>3.9- <a href="https://github.com/tomtom/tcomment_vim" target="_blank">tComment</a></h3>
A nice plug-in that automatically detects that language you're coding in and comments selected blocks when needed accordingly.
<br/>
<br/>
To install tComment on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/tcomment
```
<br/>
You can easily comment something by doing a visual select <mark>Shift + v</mark> then pressing <mark>g + c + +</mark> (yes that's a plus sign 'gc+').
<br/>
<h3>3.10- <a href="https://github.com/vim-scripts/loremipsum" target="_blank">loremipsum</a></h3>
Who doesn't know the dummy text lorem ipsum. This plug-in generates a lorem ipsum text of a certain specified length to serve as a place holder. This plug-in isn't available in the official repositories of many distributions and you'll have to get it from GitHub (and it's unmaintained since 2008).
<br/>
<br/>
Simply run:
```properties
cd ~ && git clone https://github.com/vim-scripts/loremipsum
```
<br/>
then:
```properties
cd ~/loremipsum/
```
<br/>
Now let's see what's in this directory:
```properties
ls -lh ~/loremipsum/
```
```properties
total 4.0K
drwxr-xr-x 2 firas firas  50 Sep 23 04:36 autoload
drwxr-xr-x 2 firas firas  28 Sep 23 04:36 doc
drwxr-xr-x 2 firas firas  28 Sep 23 04:36 plugin
-rw-r--r-- 1 firas firas 771 Sep 23 04:36 README
```
<br/>
So we have an autoload directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/autoload</mark>, we also have a doc directory which needs it contents to be copied to <mark>/usr/share/vim/vimfiles/doc/</mark>, and a plugin directory which needs its contents to be copied to <mark>/usr/share/vim/vimfiles/plugin</mark>. We also have a README file which won't be needed for this plug-in to work.
<br/>
<br/>
Now run:
```properties
cp -rav ~/loremipsum/autoload/ /usr/share/vim/vimfiles/autoload/
cp -rav ~/loremipsum/doc/ /usr/share/vim/vimfiles/doc/
cp -rav ~/loremipsum/plugin/ /usr/share/vim/vimfiles/plugin/
```
<br/>
Now simply run:
```none
:Loremipsum 4
```
<br/>
and you'll get 4 words from the lorem ipsum text.
<br/>
<br/>
<hr/>
<h3>3.11- <a href="https://github.com/tpope/vim-fugitive" target="_blank">fugitive.vim</a></h3>
Another awesome plug-in for Vim, from the creator of <a href="https://github.com/tpope/vim-pathogen" target="_blank">pathogen.vim</a> and <a href="https://github.com/tpope/vim-surround" target="_blank">surround.vim</a>. It's also the most popular Vim plug-in on VimAwesome. This Git wrapper adds a ton of functionality to your Vim editor and makes your life easier when working with Git as you'll never have to leave Vim to check for file changes, status, push and pull commits ...etc.
<br/>
<br/>
To install fugitive.vim on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/fugitive
```
<br/>
<hr/>
<h3>3.12- <a href="https://vimawesome.com/plugin/vim-gitgutter" target="_blank">vim-gitgutter</a></h3>
A pretty useful plug-in alongside fugitive, it shows you a git diff in the gutter to right next to your line numbers. You can easily recognize added, modified and removed lines.
<br/>
<br/>
To install vim-gitgutter on Gentoo Linux, simply run:
```properties
emerge --sync && emerge -av app-vim/gitgutter
```
<br/>
gitgutter should be automatically enabled when you edit a file in a git repository.
<br/>
<hr/>
