#!/usr/bin/env python3

# On importe numpy (pour se faciliter la vie), matplotlib et pandas
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# On lit les données du fichier csv et on sépare les deux colonnes en deux tableaux
df= pd.read_csv("data.csv")
nb_threads = df.coeurs.values
temps_sec = df.secondes.values

# On crée nos tableaux qui contiendront les valeurs à tracer
# n -> nombre de threads
# t_moy -> temps moyen selon n
# ecart_type -> écart-type en fonction de n
n = []
t_moy = []
ecart_type = []

# On rempli n en trouvant les différents nombres de threads utilisés
n.append(nb_threads[0])
for i in range(1, len(nb_threads)) :
	if nb_threads[0] == nb_threads[i] :
		break
	n.append(nb_threads[i])
		
# On rempli t_moy en calculant le temps moyen en fonction du nombre d'échantillons pour chaque nombre de threads
# val est un tableau qui va contenir les différentes valeurs associées à un certain nombre de threads afin d'en faire la moyenne		
curr = 0
while curr < len(n) :
	val = []
	i = curr
	while i < len(temps_sec) :
		val.append(temps_sec[i])
		i += len(n)
	ecart_type.append(np.std(val))
	t_moy.append(np.mean(val))
	curr += 1
	
# On trace le temps d'exécution en fonction du nombre de threads en bleu avec un trait plein de 1 pixel d'épaisseur
plt.errorbar(n, t_moy, yerr=ecart_type, ecolor='red')

# Limiter le range de valeurs affichées pour l'axe x (abscisses)
plt.xlim(1, len(n))

# Forcer la graduation en x. np.linspace découpe l'intervalle [1, len(n)] en len(n) parties égales
plt.xticks(np.linspace(1, len(n), len(n)))

# Donner un label à l'axe x
plt.xlabel('Nombre de threads')

# Donner un label à l'axe y
plt.ylabel('Temps moyen (secondes)')

# Donner un titre au graphe.
plt.title("Mesures de performance")

# Permet d'ajouter une grille au graphe, rendant la lecture de vos données plus facile.
plt.grid(True)

# On enregistre les graphiques. L'extension est directement déduite du nom donné en argument (png par défault).
plt.savefig("Graphes_python.png")
plt.savefig("Graphes_python.pdf")

# Optionnel : on affiche le graphe à l'écran (note: show est un appel bloquant, tant que le graphe n'est pas fermé, on est bloqué)
plt.show()

# On ferme proprement le plot.
plt.close()
