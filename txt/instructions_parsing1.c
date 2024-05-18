structures de départ :

/*	structure for environment variables
*/
typedef struct s_var_env
{
	char				*name;
	char				*value;
	struct s_var_env	*next;
	struct s_var_env	*previous;
}	t_var_env;



/*	structure storing one redirection and point to the next
	type	: 1 == <, 2 == >, 4 == <<, 3 == >>
	arg		: filename or delimiter
*/
typedef struct s_redirect
{
	int					type;
	char				*arg;
}	t_redirect;



/*	structure for one command to execute 
	cmd		: cmd path, flags and arg
	io		: all redirection stored in list
*/
typedef struct s_cmd
{
	char			**arg;
	t_list			*io;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;




/*	structure holding the whole command line,
*	reset after execution
*/
typedef struct s_line
{
	t_cmd			*cmd;
	char			**env;
	int				pipe[2][2];
	int				fd_std[2];
	int				n_cmds;
	int				exit_status;
	t_var_env		*lst_env;
	struct termios	old;
	int				term_status;
}	t_line;


                Parcourir jusqu''a trouver des quotes OU un pipe OU la '\0'
                
si je trouve une quote :
    - verifier que la quote se referme
    - si la quote se referme : on skip tout ce qu''il y a a l''interieur, les pipes dans 
	des quotes ne comptent pas pour diviser les blocs
si je trouve un pipe :
    - je stock tout ce que j''ai recup dans une variable
    - je formate* la variable  ET je la met dans un element de la liste
    - on recommence jusqu'a '\0'
si je trouve un '\0' :
    - je met tout dans un element de la liste en la formatant*
si je trouve un export :
    - le egal doit etre coller (format : mot=truc)
    - faire un arg avec tout ce qu''il ya avant le =
    - faire un bloc avec ce qu''il y a apres le = jusqu au prochain espace ou '\0'
    - si ya rien apres le egal = arg NULL
A la fin :
	- faire un split_bis (split en fonction des withespace ET qui skip les quotes)
	- clear toutes les quotes
	- tout mettre dans des list de cmds

                            *Formater la ligne recuperee

- Parcourir et voir si je trouve une quote simple ou un $ :
    - si quote : parcourir jusqu''a ce que la quote se referme (donc s''il y a un $ -> ne pas expand)
    - sinon : Si il y a un $, le remplacer par sa valeur dans l''env 
    - si $? : remplacer par exit_status (faut convertir >:()
    - si ya un $ avec rien apres on fait rien
    - si un $ ne correspond a rien, remplacer par une chaine vide
	- si $ avec une suite de chiffre, remplacer par la suite de chiffre SANS le 1er chiffre (ex: $1234 -> 234)
- Parcourir pour chercher les redirections
    - Juste apres la redirection:
        - Si il n y a rien apres : erreur de parsing
        - Si il ya un nom -> c''est arg   
		- mettre tout dans la list de redirections et clear la redirection dans la commande
- Gestion des quotes et des $ pour les exports
	- Apres avoir remplacer les $ par leur valeur dans l''env
		- verifier si la valeur contient des caractéres ' ou " ou symboles de redirections
'		- mettre des \ avant chacun de ces caractéres (pour noter qu'il ne faut pas les clear)
		- penser a proteger les caractéres \ 
		- clear les \ a la fin du parsing

                    A la fin, reparcourir la liste des redirection io

- Si je trouve une redirection de type 2 (<<), appeler la fonction here_doc
- dans le here_doc : interpreter les $ sauf si le delimiteur est entre quotes

                        exemple structure des lignes de commandes

echo "coucou | hello" | echo $USER '$USER' < log
echo 'coucou | hello' | echo $USER '$USER' < log

arg[0][0] = echo
arg[0][1] = coucou | hello
arg[1][0] = echo
arg[1][1] = loulou 
arg[1][2] = $USER
arg[1]->io->type = 0
arg[1]->io->arg = log

                        Exemples chiants a tester:

echo '"'"$USER"'"'		  >>>	  "saperrie"
echo """"$USER""""         >>>		saperrie
echo "\"""$USER""\""        >>>		"saperrie"
echo "\\"""$USER""\\""		 >>>	 \saperrie\
echo "\\"""$USER"""\\"""	  >>>	  \saperrie\
export test=$test"coucou"
echo mdrr 1<>coucou
echo mdrr 2<>coucou
echo coucou > "ihi aha"ihi
echo >mdr>hey>>sarace \sal"mdr"
echo <hey1<h'ey2'
echo bonjour >hey >>hey2 >>hey3
>> e
ls $HOME/Desktop
echo “$PATH”
echo "$PATH$PWD"
echo -n a '' b '' c '' d
e"ch"o bonjour
echo\ bonjour
exit ' 3'
exit -1
exit -9223372036854775808
exit 9223372036854775807
exit +3 
exit 2000000
exit -2147483649
exit 0 bonjour ->	bash: exit: too many arguments
exit coucou    ->	exit: coucou: numeric argument required
cat Makefile | ./minishell
Essayer d''exécuter un mini shell dans minishell ./minishell et tester les signaux et le man de commandes
./minishell coucou (doit renvoyer une erreur)
echo "$ejnzefc" hey
./minishell 2>lol (redirection de stderr, aucuns messages d'erreurs ne doivent s'imprimer dans le terminal)
env -i ./minishell (= lance sans les var d’env)
export TEST='""' -> puis echo "$TEST"
export test='""' puis echo "'$test'"
export test="''" puis echo $test ''
export test='echo $USER C"es"t'
export test='echo C"est > $out'
$test (avec test vide)
echo \\ 
echo "\" 
echo coucou > "ihi aha"ihi
export test=truc
| echo coucou
export test="\"
echo' a'
tab
cat <<"<<""<"
<<"<">>"<"
<< ""
>>> log 
>>>>> log
> >> log
><<log
> log2
">"
|
|||||||
echo $
echo hello |
<"" 
export TEST='""'
yes $USER
exp"$hello"ort""''""
export test="truc truc"
echo $ejknfenf hey
export cmd="echo 'bonjour""ihi'"
export lol2="\'" puis echo $lol2
export TEST="''" -> puis echo $TEST
export TEST='""' -> puis echo $TEST
<< 'test' et << "test" ne doivent pas gerer les expansions
export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=l M=m N=n O=o P=p Q=q R=r
unset A B C D E F G H I J K L M N O P Q R
cat Makefile > z | cat z | wc -l > r | ls
echo "$""USER"

dans le here_doc :
<< 'test' et << "test" ne doivent pas gerer les $
<< $USER
 
export path=
=> afficher test dans env ET export

export path
=> afficher test dans export mais PAS dans env

export "ceci"="cela"
export lol=""
export lol=" "
export lol2=''
export lol2=' '
export lol2="\'"
export lol2="'"
export lol2="'"
export lol2="\\"
export lol2='$'
export lol2='\t'
export test=hello hello="poulette"
export test2=
export test1
export test= o
!!export test=$test"coucou"
export zz zzz= zzzz=asd
export ?=42
export $
export 1=a
BOUNJOUR="\'\\"  then $BONJOUR gives \'\: command not found
export BONJOURJESUIS =a
export BONJOUR\\JESUIS=a
export BONJOUR\'JESUIS=a
export BONJOUR\&JESUIS=a 
export BONJOUR\|JESUIS=a
export BONJOUR\;JESUIS=a
export 'AH\'=nop
export 'AH@'=nop
export 'AH"'=nop
export 'AH!'=nop
export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C
export "  a"=coucou
export _test=quelquechose puis echo $test

unset quelque chose qui n'existe pas
unset plusieurs trucs a la fois
 
echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e
cat /dev/random | head -c 100 | wc -c
ls asdfasdf | echo a
echo a | ls asdfasdf

#Boucle infinie : (ne pas segfault)
cat -e /dev/random | head -c 10
cat -e /dev/random | cat -e | head -c 10
cat -e /dev/random | cat -e | cat -e | head -c 10

##########Protections#########
'echo' "bonjour" "wesh"
e"ch"o bonjour
       'ech'o bonjour
'echo "$HOME"'
echo '''''' | cat -e

##########Redirections#########
cat < test.txt
cat <test.txt >>hello<bonjour
cat "<test.txt"
echo bonjour1>test1
echo bonjour 1>test2
echo bonjour > "     test1"
echo bonjour 2>hey test2
#double redirection
echo bonjour >> test3
echo bonjour>>test3>>test4
1>test1 2>test2 echo bonjour
1>test12>test2 echo bonjour
>test1 2>test2 echo bonjour
>> e
echo bonjour 1> "$PATHH"


#########Environnement#########
echo "$'PATH'"
echo $"coucou"
echo $PATH
ls $HOME/Desktop
echo "$PATH""" coucou
echo $PATH"coucou"
echo "hello"$PWD"coucou"
coucou$PWD test$COLORTERMlol lol$HOME
echo "bonjour$PATH$PWD"
echo "bonjour\$PATH$PWD"
echo $PATH"coucou"
echo $$$$$$$$
echo $12345
echo $$ -> affiche le pid mais franchement c'est pas demander flemme

