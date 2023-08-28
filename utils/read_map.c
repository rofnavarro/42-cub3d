#include	"../raycaster.h"

char	*read_map(char *map)
{
	FILE	*file;
	long	len;
	char	*ret;

	file = fopen(map, "r");
	if (file == NULL)
		return NULL;
	fseek(file, 0L, SEEK_END);
	len = ftell(file);
	fseek(file, 0L, SEEK_SET);

	ret = (char *)calloc(len, sizeof(char));
	if (ret == NULL)
		return NULL;
	fread(ret, sizeof(char), len, file);
	fclose(file);
	return (ret);
}
