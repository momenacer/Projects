<h1 align="center">« Harvard » vs « Von Neumann » </h1>


L'architecture de [**von Neumann**](https://user-images.githubusercontent.com/127967325/227723834-b217ce67-13ab-4b72-8dda-421db39ae60e.png)
 et l'architecture de [**Harvard**](https://user-images.githubusercontent.com/127967325/227723856-46cd91cb-26b3-49b4-9a8a-19af8e5181ac.png)
 sont deux modèles différents de conception de l'ordinateur. L'architecture de **von Neumann** est le modèle le plus courant et est utilisé dans la plupart des 
 ordinateurs modernes, tandis que l'architecture de **Harvard** est souvent utilisée dans les systèmes embarqués et les microcontrôleurs.

![image](https://user-images.githubusercontent.com/127967325/227724135-96353f30-732f-41dd-a1bf-84942fe9cc7d.png)

💻 La principale différence entre les deux architectures réside dans la manière dont elles gèrent la mémoire.  
  > 📄 L'architecture de **von Neumann** utilise une mémoire commune pour stocker à la fois les données et les instructions du programme,  
  > 📄 L'architecture de **Harvard** utilise deux mémoires séparées pour stocker les instructions
et les données.    

  > ⚡  L'architecture de **von Neumann**, les instructions et les données sont toutes stockées dans la même mémoire et sont traitées par le processeur selon les mêmes
  règles. Le processeur lit les instructions de la mémoire et les exécute séquentiellement, en accédant aux données nécessaires dans la même mémoire.  
  > ⚡  L'architecture de **Harvard** utilise deux mémoires séparées pour stocker les instructions et les données. Cette approche permet de traiter les
  instructions et les données de manière indépendante, ce qui peut entraîner des performances plus rapides. 
  
  🤝   _**En résumé**, l'architecture de **von Neumann** et l'architecture de **Harvard** sont deux modèles différents de conception de l'ordinateur qui diffèrent principalement dans 
  la manière dont elles gèrent la mémoire. L'architecture de von Neumann utilise une mémoire commune pour les données et les instructions, tandis que l'architecture 
  de Harvard utilise deux mémoires séparées pour stocker les données et les instructions. Bien que l'architecture de Harvard puisse offrir des performances plus rapides
  dans certaines applications, elle peut également être plus coûteuse et plus complexe à programmer._
 
_________________________________________________________________________________________________________________________________________________________________________  
  
 <h1 align="center">« RISC » and « CISC » </h1>

Les architectures de processeurs RISC ([Reduced Instruction Set Computing](https://user-images.githubusercontent.com/127967325/227725255-5226c468-6134-4f8f-b071-090002e58828.jpg)
) et CISC ([Complex Instruction Set Computing](https://user-images.githubusercontent.com/127967325/227725212-d9230f5c-445d-4c20-86ce-246a119a82dd.jpg)) diffèrent par
la façon dont les instructions sont traitées et exécutées. 

![image](https://user-images.githubusercontent.com/127967325/227725662-fdda53ca-09b6-4bf9-9c15-c3af625e1933.png)

💻 Voici quelques explications sur les différences entre ces deux architectures :

📝 **Complexité des instructions :** 
> Les processeurs CISC ont des instructions complexes qui peuvent effectuer plusieurs tâches simultanément, ce qui signifie qu'une
seule instruction peut prendre plusieurs cycles d'horloge pour s'exécuter. En revanche, les processeurs RISC ont des instructions simples qui ne font qu'une seule
tâche à la fois, mais qui s'exécutent en un seul cycle d'horloge.  

📝 **Taille des instructions :**
> Les instructions dans les processeurs RISC sont généralement plus courtes que celles des processeurs CISC, car elles ne contiennent
que les informations nécessaires pour effectuer une seule tâche. Les instructions CISC, en revanche, sont souvent plus longues et plus complexes, car elles peuvent
effectuer plusieurs tâches simultanément.  

📝 **Registres :**
> Les processeurs RISC ont souvent plus de registres que les processeurs CISC. Cela permet de stocker plus de données dans les registres plutôt 
que dans la mémoire vive, ce qui peut accélérer les opérations.  

📝 **Précharge des données :**
> Les processeurs RISC n'ont pas de précharge de données intégrée, ce qui signifie que le processeur doit accéder à la mémoire chaque 
fois qu'il a besoin de données. Les processeurs CISC, en revanche, ont souvent une précharge de données intégrée, qui permet de stocker des données fréquemment 
utilisées en mémoire cache.  

📝 **Utilisation de la mémoire vive :**
> Les processeurs RISC ont tendance à utiliser moins de mémoire vive que les processeurs CISC, car ils stockent plus de
données dans les registres. Cela peut réduire le temps d'accès à la mémoire vive et améliorer les performances globales du système.  

🤝  _**En résumé**, les processeurs RISC ont des instructions simples et exécutent une seule tâche à la fois, mais ils peuvent accéder plus rapidement aux données en mémoire
vive grâce à une mémoire cache plus grande et une utilisation plus efficace des registres. Les processeurs CISC ont des instructions plus complexes qui peuvent 
effectuer plusieurs tâches simultanément, mais ils peuvent nécessiter plus de cycles d'horloge pour s'exécuter et ont souvent besoin de plus de mémoire vive. Le choix
entre les deux dépend des besoins spécifiques de l'application._


_________________________________________________________________________________________________________________________________________________________________________



<h3 align="left">Languages and Tools:</h3>
<p align="left"> <a href="https://developer.android.com" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/android/android-original-wordmark.svg" alt="android" width="40" height="40"/> </a> <a href="https://www.arduino.cc/" target="_blank" rel="noreferrer"> <img src="https://cdn.worldvectorlogo.com/logos/arduino-1.svg" alt="arduino" width="40" height="40"/> </a> <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> </a> <a href="https://couchdb.apache.org/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/0d6c64dbbf311879f7d563bfc3ccf559f9ed111c/icons/couchdb/couchdb-original.svg" alt="couchdb" width="40" height="40"/> </a> <a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> <a href="https://www.w3schools.com/cs/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/csharp/csharp-original.svg" alt="csharp" width="40" height="40"/> </a> <a href="https://www.figma.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/figma/figma-icon.svg" alt="figma" width="40" height="40"/> </a> <a href="https://git-scm.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/git-scm/git-scm-icon.svg" alt="git" width="40" height="40"/> </a> <a href="https://www.w3.org/html/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/html5/html5-original-wordmark.svg" alt="html5" width="40" height="40"/> </a> <a href="https://www.adobe.com/in/products/illustrator.html" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/adobe_illustrator/adobe_illustrator-icon.svg" alt="illustrator" width="40" height="40"/> </a> <a href="https://www.java.com" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/java/java-original.svg" alt="java" width="40" height="40"/> </a> <a href="https://developer.mozilla.org/en-US/docs/Web/JavaScript" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/javascript/javascript-original.svg" alt="javascript" width="40" height="40"/> </a> <a href="https://www.linux.org/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" alt="linux" width="40" height="40"/> </a> <a href="https://www.mathworks.com/" target="_blank" rel="noreferrer"> <img src="https://upload.wikimedia.org/wikipedia/commons/2/21/Matlab_Logo.png" alt="matlab" width="40" height="40"/> </a> <a href="https://www.php.net" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/php/php-original.svg" alt="php" width="40" height="40"/> </a> <a href="https://postman.com" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/getpostman/getpostman-icon.svg" alt="postman" width="40" height="40"/> </a> <a href="https://www.python.org" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/python/python-original.svg" alt="python" width="40" height="40"/> </a> <a href="https://pytorch.org/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/pytorch/pytorch-icon.svg" alt="pytorch" width="40" height="40"/> </a> <a href="https://reactjs.org/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/react/react-original-wordmark.svg" alt="react" width="40" height="40"/> </a> <a href="https://reactnative.dev/" target="_blank" rel="noreferrer"> <img src="https://reactnative.dev/img/header_logo.svg" alt="reactnative" width="40" height="40"/> </a> <a href="https://unity.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/unity3d/unity3d-icon.svg" alt="unity" width="40" height="40"/> </a> <a href="https://vuejs.org/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/vuejs/vuejs-original-wordmark.svg" alt="vuejs" width="40" height="40"/> </a> </p>



<p><img align="center" src="https://github-readme-streak-stats.herokuapp.com/?user=momenacer&" alt="momenacer" /></p>

<h3 align="left">Social Media</h3>

<p align="left">
<a href="https://codesandbox.io/u/momenacer" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/codesandbox.svg" alt="https://codesandbox.io/u/momenacer" height="30" width="40" /></a>
<a href="https://www.facebook.com/profile.php?id=100009667802416" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/facebook.svg" alt="mohi" height="30" width="40" /></a>
<a href="https://instagram.com/mohi_mncr" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/instagram.svg" alt="mohi_mncr" height="30" width="40" /></a>
<a href="https://dribbble.com/mncr" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/dribbble.svg" alt="mncr" height="30" width="40" /></a>
<a href="https://www.codechef.com/users/mohi" target="blank"><img align="center" src="https://cdn.jsdelivr.net/npm/simple-icons@3.1.0/icons/codechef.svg" alt="mohi" height="30" width="40" /></a>
</p>
