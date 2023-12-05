/*
 *	Fonctions a ecrire
 *
 * 	Si ya un 's' a la fin de "strs", c'est un tableau de strs (char**)
 *
 */





// * retourne la taille d'un char**
int	ft_strs_size(char **strs)
{

}


// * free tous les char * puis le char**
int	ft_free_strs(char **strs)
{

}


// * duplique un char**  (tableau de char*) (copie de envp par exple)
// * CE N'EST PAS  ft_strdup !
char	**ft_strsdup(char **strs)
{

}



//*	enleve les white spaces au debut et a la fin d'une str
//* envoit une copie ou modifie l'originale ?
char	*ft_strtrim_whitespaces(char const??? *str)
{

}


int	ft_str_starts_with(char *str, char *start)
{

}

int	ft_str_ends_with(char *str, char *start)
{

}


//* si 2 chaines de characteres sont STRICTEMENT identiques
int	ft_str_equals(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)+1) == 0);
}

