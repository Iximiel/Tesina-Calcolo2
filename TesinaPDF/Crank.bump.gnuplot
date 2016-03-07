set table "Crank.bump.table"; set format "%.5f"
set samples 501.0; plot [x=-1.5:1.5] abs(x)<1? exp(-1/(1-x*x)) :0
