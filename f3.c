#include "main.h"
/**
* _getpath --
* @cmd: --
* Return: --
*/
char *_getpath(char *cmd)
{
	char *epath, *ccmd, *dr;
	int i;
	struct stat sts;

	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] == '/')
		{
			if (stat(cmd, &sts) == 0)
			return (_dup(cmd));
			return (NULL);
		}
	}

	epath = _getenv("PATH");
	if (!epath)
		return (NULL);

	dr = strtok(epath, ":");
	while (dr)
	{

		ccmd = malloc(_len(dr) + _len(cmd) + 2);
		if (ccmd)
		{
			_cpy(ccmd, dr);
			_cat(ccmd, "/");
			_cat(ccmd, cmd);
			if (stat(ccmd, &sts) == 0)
			{
			free(epath);
			return (ccmd);
			}
			free(ccmd), ccmd = NULL;
			dr = strtok(NULL, ":");
		}
	}
	free(epath);
	return (NULL);
}
/**
* _getenv --
* @var: --
* Return: --
*/
char *_getenv(char *var)
{
	char *tmp, *key, *val, *env;
	int i;

	for (i = 0; environ[i]; i++)
	{
		tmp = _dup(environ[i]);
		key = strtok(tmp, "=");
		if (_cmp(key, var) == 0)
		{
			val = strtok(NULL, "\n");
			env = _dup(val);
			free(tmp);
			return (env);
		}
		free(tmp), tmp = NULL;
	}
	return (NULL);
}
/**
* _readline --
* Return: --
*/
char *_readline(void)
{
	char *l = NULL;
	size_t len = 0;
	ssize_t n;

	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);
	n = getline(&l, &len, stdin);
	if (n == -1)
	{
		free(l);
		return (NULL);
	}
	return (l);
}
