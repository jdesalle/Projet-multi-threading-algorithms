#!/usr/bin/env python3

# On importe numpy (pour se faciliter la vie), matplotlib et pandas
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys

# On lit les données du fichier csv et on sépare les deux colonnes en deux tableaux
name = sys.argv[1]
namebis = sys.argv[2]
df= pd.read_csv("{}.csv".format(name))
nb_threads = df.coeurs.values
temps_sec = df.secondes.values

dfbis= pd.read_csv("{}.csv".format(namebis))
nb_threadsbis = dfbis.coeurs.values
temps_secbis = dfbis.secondes.values

# On crée nos tableaux qui contiendront les valeurs à tracer
# n -> nombre de threads
# t_moy -> temps moyen selon n
# ecart_type -> écart-type en fonction de n
n = []
t_moy = []
ecart_type = []

t_moybis = []
ecart_typebis = []

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

curr = 0
while curr < len(n) :
	val = []
	i = curr
	while i < len(temps_secbis) :
		val.append(temps_secbis[i])
		i += len(n)
	ecart_typebis.append(np.std(val))
	t_moybis.append(np.mean(val))
	curr += 1
	
# On trace le temps d'exécution en fonction du nombre de threads en bleu avec un trait plein de 1 pixel d'épaisseur
plt.errorbar(n, t_moy, yerr=ecart_type, ecolor='red', label="avec la librairie C")
plt.errorbar(n, t_moybis, yerr=ecart_typebis, ecolor='green', label="avec nos primitives d'attente active")

plt.legend()

# Limiter le range de valeurs affichées pour l'axe x (abscisses)
plt.xlim(n[0]-0.1, n[-1]+0.1)

# Débuter l'axe y à 0 (ordonnées)
plt.ylim(ymin=0)

# Forcer la graduation en x. np.linspace découpe l'intervalle [1, len(n)] en len(n) parties égales
plt.xticks(np.linspace(n[0], n[-1], len(n)))

# Donner un label à l'axe x
plt.xlabel('Nombre de threads')

# Donner un label à l'axe y
plt.ylabel('Temps moyen (secondes)')

# Donner un titre au graphe.
plt.title("Mesures de performance")

# Permet d'ajouter une grille au graphe, rendant la lecture de vos données plus facile.
plt.grid(True)

# On enregistre les graphiques. L'extension est directement déduite du nom donné en argument (png par défault).
plt.savefig("{}.png".format(name))
plt.savefig("{}.pdf".format(name))
