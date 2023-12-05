/*


Parsing (sans la gestion des parentheses du bonus)



on a data->line qui vaut un truc du genre :

   echo    -n     -n   'hello $USER'  "salut $USER"  def  > file.txt && env | sort




On veut transformer ca en [tableau ou liste chainee] de tokens:


|	val			| type				| escape_env_var
|	-----------	| -----------		|-----------------
|	echo		| TK_TYPE_STR		|	0
|	-n			| TK_TYPE_STR		|	0
|	-n			| TK_TYPE_STR		|	0
|	hello $USER	| TK_TYPE_STR		|	 1
|	salut $USER	| TK_TYPE_STR		|	0
|	def			| TK_TYPE_STR		|	0
|	>			| TK_TYPE_RED_OUT	|	0
|	file.txt	| TK_TYPE_STR		|	0
|	&&			| TK_TYPE_AND		|	0
|	env			| TK_TYPE_STR		|	0
|	|			| TK_TYPE_PIPE		|	0
|	sort		| TK_TYPE_STR		|	0





ALGO :


parcourir line

	if is_white_space current_char
		current_char++

	else if current_char est dans "&|><"
		regarder si le char d'apres est identique ( >> ou << ou && ou ||)
		creer un token avec 1 OU 2 char et definir son type (ex: TK_TYPE_RED_OUT)

	else if current_char == doubleQuote
		chercher doubleQuote suivante et creer un token entre ces 2 doubleQuotes (ft_substr)
		si ya pas de doubleQuote fermante; afficher erreur ou return null... (On a pas a gerer)
		token.type = TK_TYPE_STR
		token.escape_env_var= false

	else if current_char == simpleQuote
		... la meme chose
		token.escape_env_var= true

	else
		(( on n'est ni sur un operateur, ni sur une quote ))
		chercher la fin du mot et creer un token entre ces 2 char(ft_substr)
			==> (tant que char existe && char n'est pas dans "&|><(whiteSpace)" )
		token.type = TK_TYPE_STR
		token.escape_env_var= false

































*/