#!/bin/bash
#By Richy501
#Language Spanish by personal using
#Version 1.0
logeo(){
	echo "Opcion de logearse elegida"
	echo "Introduce tu nombre"
	read name
	echo "Introduce tu email"
	read email
	#read -s contra
	#Aqui conectamos al git
	echo "Tu nombre: " $name " y tu email: " $email
	git config --global user.name $name
	git config --global user.email $email
	echo "Conexion realizada con exito"
}

clon(){
	echo "Introduce la ruta que quieres clonar"
	read ruta
	git clone $ruta
}


gihub(){
	echo "Pon la ruta del repositorio"
	read repo
	git remote add origin $repo
	git push origin master
	echo "El proyecto se ha guardado en Github"
}

save(){
	echo "Introduce el nombre del commit"
	read com
	git add .
	git commit -m "$com"
	echo "El proyecto se ha guardado localmente"
	echo "Quieres guardarlo en Github? 1-yes 2-no"
	read opc
	case $opc in
		1) echo "Pon la ruta del repositorio"
			read repo
			git remote add origin $repo
			git push origin master
			echo "El proyecto se ha guardado en Github";;
		*) echo "No se ha guardado en Github";;
	esac
}

syn(){
	echo "Pon la ruta del repositorio a sincronizar"
	read repo
	git pull $repo
}
echo "--------------------------------------------------------------|"
echo "|Bienvenido al script para git"
echo "|Recuerda que todas las opciones se haran dentro de la carpeta|"
echo "|que tengas el script"
echo "--------------------------------------------------------------|"
op=0
#Dara vueltas hasta que la opcion sea mayor a 5
while [ $op -le 5 ]
do
	echo "----------------------------------"
	echo "Elige una opcion"
	echo "1. Registrarse"
	echo "2. Clonar"
	echo "3. Guardar el trabajo de forma local/github"
	echo "4. Sincronizar el trabajo desde github"
	echo "6. Salir"
	read op
	case $op in
		1) logeo;;
		2) clon;;
		3) save;;
		4) syn;;
		*) echo "Adios";;
	esac
done
