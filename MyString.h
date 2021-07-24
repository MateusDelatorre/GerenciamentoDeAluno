#ifndef MyString
#define MyString

void copiaString(char *destino, char *origem){
    for (; *origem; origem++, destino++)
    {
        *destino = *origem;
    }
	*destino = 0;
}

int isMaiusculo(char caracter){
    if (caracter >= 'A' && caracter <= 'Z') {
        return 1;
    }
    return 0;
}

int toLower(char caracter){
	if (isMaiusculo(caracter)) {
		caracter += 32;
	}
	return caracter;
}

int sortString(char *string_maior, char *string_menor){
    for (; *string_menor; string_menor++, string_maior++)
    {
        if(toLower(*string_maior) == toLower(*string_menor)) continue;
		if(toLower(*string_maior) < toLower(*string_menor))
			return 1;
		else
			return 0;
    }
    return 1;
}

#endif