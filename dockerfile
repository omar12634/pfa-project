# Utiliser une image NGINX officielle
FROM nginx:latest

# Supprimer la config par défaut de NGINX
RUN rm /etc/nginx/conf.d/default.conf

# Ajouter notre propre configuration NGINX
COPY nginx.conf /etc/nginx/conf.d/default.conf

# Copier le contenu de l'application (index.html et autres fichiers) dans le conteneur
COPY . /usr/share/nginx/html/

# Exposer le port 80 (déjà fait par l'image NGINX)
EXPOSE 80

