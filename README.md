Comunicación Segura de Imágenes con Sockets y AES en C++
Este proyecto demuestra cómo establecer una comunicación segura entre un cliente y un servidor utilizando sockets en C++ y cifrado AES. Se enfoca en la transmisión de imágenes, asegurando su confidencialidad durante el envío.

Características
Cifrado AES: Implementación de cifrado simétrico para proteger los datos transmitidos.

Sockets en C++: Uso de sockets para la comunicación entre cliente y servidor.

Transmisión de Imágenes: Envío y recepción de archivos de imagen de forma segura.

Docker: Contenedores Docker para facilitar la configuración y ejecución del entorno.

Estructura del Proyecto
bash
Copiar
Editar
.
├── client/                 # Código fuente del cliente
│   └── client.cpp
├── server/                 # Código fuente del servidor
│   └── server.cpp
├── Dockerfile              # Archivo para construir la imagen Docker
├── docker-compose.yml      # Configuración de Docker Compose
└── README.md               # Documentación del proyecto
Requisitos
C++17 o superior

OpenSSL para funciones de cifrado

Docker y Docker Compose (opcional, para ejecución en contenedores)

Instalación y Ejecución
Opción 1: Usando Docker
Clona el repositorio:

bash
Copiar
Editar
git clone https://github.com/JuanSeRestrepoNieto/final-analisis-alg.git
cd final-analisis-alg
Construye y levanta los contenedores:

bash
Copiar
Editar
docker-compose up --build
Esto iniciará tanto el servidor como el cliente en contenedores separados.

Opción 2: Compilación Manual
Clona el repositorio y navega a la carpeta correspondiente:

bash
Copiar
Editar
git clone https://github.com/JuanSeRestrepoNieto/final-analisis-alg.git
cd final-analisis-alg
Compila el servidor:

bash
Copiar
Editar
g++ -std=c++17 server/server.cpp -o server -lssl -lcrypto
Compila el cliente:

bash
Copiar
Editar
g++ -std=c++17 client/client.cpp -o client -lssl -lcrypto
Ejecuta el servidor:

bash
Copiar
Editar
./server
En otra terminal, ejecuta el cliente:

bash
Copiar
Editar
./client
Uso
Asegúrate de que el servidor esté en ejecución.

El cliente leerá una imagen desde el sistema de archivos, la cifrará utilizando AES y la enviará al servidor a través de sockets.

El servidor recibirá la imagen cifrada, la descifrará y la almacenará o procesará según sea necesario.

Contribuciones
Las contribuciones son bienvenidas. Por favor, abre un issue o envía un pull request para discutir cambios importantes.

Licencia
Este proyecto está licenciado bajo la Licencia MIT. Consulta el archivo LICENSE para más detalles.