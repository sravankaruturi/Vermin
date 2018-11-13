set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=110
highlight ColorcColumn ctermbg=darkgray

augroup project
	autocmd!
	autocmd BufRead,BufNewFile *.h, *.c, *.cpp set filetype=c++.doxygen
augroup END

set path+=**

nnoremap <F5> :! cd ./cmake-build-debug/; make; ./Game<cr>
"nnoremap <F5> :!./cmake-build-debug/Game<cr>
