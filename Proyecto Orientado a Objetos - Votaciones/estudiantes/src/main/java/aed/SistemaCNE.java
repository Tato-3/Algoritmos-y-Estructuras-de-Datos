package aed;
import java.util.Arrays;

public class SistemaCNE {
    private String[] partidos;
    private String[] distritos;
    private int[] bancasEnDisputa;
    private int[] mesasDistritos;
    private int[] votosPresidente;
    private int[][] votosDiputados;


    private maxHeapTuplas[] resultadosDeDiputados;

    private int[][] bancasPorPartido;

    private boolean[] bancasYaCalculadas;
    private int[] balotaje;
    private int votosTotalesParaPresidente;


    public class VotosPartido{
        private int presidente;
        private int diputados;
        VotosPartido(int presidente, int diputados){this.presidente = presidente; this.diputados = diputados;}
        public int votosPresidente(){return presidente;}
        public int votosDiputados(){return diputados;}
    }


    // Generamos una clase llamada tuplasDPP que va a ser una tupla que contiene dos elementos, 
    // los votos a Diputados y el idPartido al que corresponden los respectivos votos.

    public class tuplasDPP{ // Tuplas de 
        private int votosDipu;
        private int idPartido;
        tuplasDPP(int votosDipu, int idPartido)
        {this.votosDipu = votosDipu; this.idPartido = idPartido ;}
        public int obtenerVotosDipu(){return votosDipu;}
        public int obtenerIdDelPartido(){return idPartido;}
    }

    // Generamos una clase llamada maxHeapTuplas que básicamente, como su nombre indica, es una clase que se utiliza para armar Max-Heaps
    // que en general, los Heaps son de Arrays de int, en este caso se utiliza para Arrays de las tuplasDPP, clase que creamos arriba.

    public class maxHeapTuplas{ // Este Heap esta pensado para MAX-HEAPS únicamente.
        private tuplasDPP[] heapDeTuplas;
        private int tamaño;
        private int capacidad;


        public maxHeapTuplas(tuplasDPP [] arraytupla,int capacidad){ // O(n)
           this.capacidad = capacidad;
           this.tamaño = arraytupla.length;
           heapDeTuplas = arraytoheap(arraytupla);  // O(n)
        }

        // Esta función de "arraytoheap" es básicamente el algoritmo de Floyd que se utiliza para construir un heap a partir de un array.
        // En las teoricas probaron que tiene complejidad O(n) y por ello lo utilizamos para heapificar rápidamente nuestro array de tuplas.

        private tuplasDPP[] arraytoheap(tuplasDPP [] arr){  // O(n) siendo n el número de elementos/tuplas en el array.
            for (int i = arr.length / 2 - 1; i >= 0; i--) {
                heapifyDownarr(i,arr);
            }
            return arr;
        }
        
        // Este heapifyDownarr se utiliza cuando se inicializa un objeto maxHeapTuplas, para que directamente al darle un array a la clase
        // automáticamente se heapifique el array que recibe. Este truco se utiliza al final de la función registrarMesa para ir pisando los 
        // arrays heapificados en base a votosDiputados que va guardando los registros consecutivos de mesa y por lo tanto contiene los
        // votos a diputados por distrito totales. Luego esos arrays heapificados se guardan en la variable privada del sistema resultadosDeDiputados.

        private void heapifyDownarr(int indice,tuplasDPP [] arr) { // O(log(n)) siendo n el número de elementos/tuplas en el array.
            int HijoIzq = 2 * indice + 1;
            int HijoDer = 2 * indice + 2;
            int mayor = indice;

            if (HijoIzq < arr.length && compararTuplasDPP(arr[HijoIzq], arr[mayor]) > 0) {
                mayor = HijoIzq;
            }

            if (HijoDer < tamaño && compararTuplasDPP(arr[HijoDer], arr[mayor]) > 0) {
                mayor = HijoDer;
            }

            if (mayor != indice) {
                swapArr(indice, mayor,arr);
                heapifyDownarr(mayor,arr);
            }
        }

        private void swapArr(int i, int j, tuplasDPP[] arr){ // O(1)
            tuplasDPP temporal = arr[i];
            arr[i] = arr[j];
            arr[j] = temporal;
        }
    
        private int indiceHijoIzquierdo(int indicePadre) { // O(1)
            return 2 * indicePadre + 1; // O(1)
        }
    
        private int indiceHijoDerecho(int indicePadre) { // O(1)
            return 2 * indicePadre + 2; // O(1)
        }

        private void swap(int i, int j){ // O(1)
            tuplasDPP temporal = heapDeTuplas[i]; // O(1)
            heapDeTuplas[i] = heapDeTuplas[j]; // O(1)
            heapDeTuplas[j] = temporal; // O(1)
        }

        // Este heapifyDown en la función resultadosDiputados para re-heapificar cada vez que se modifica la tupla con más votos para asignar una banca.

        private void heapifyDown(int indice) { // O(log(n)) siendo n el número de elementos/tuplas en el array.
            int indiceHijoIzquierdo = indiceHijoIzquierdo(indice);
            int indiceHijoDerecho = indiceHijoDerecho(indice);
            int mayor = indice;

            if (indiceHijoIzquierdo < tamaño && compararTuplasDPP(heapDeTuplas[indiceHijoIzquierdo], heapDeTuplas[mayor]) > 0) {
                mayor = indiceHijoIzquierdo;
            }

            if (indiceHijoDerecho < tamaño && compararTuplasDPP(heapDeTuplas[indiceHijoDerecho], heapDeTuplas[mayor]) > 0) {
                mayor = indiceHijoDerecho;
            }

            if (mayor != indice) {
                swap(indice, mayor);
                heapifyDown(mayor);
            }
        }

        public tuplasDPP mirarElMax() { // O(1)
            tuplasDPP max = heapDeTuplas[0]; // O(1)
            return max; // O(1)
        }

        public void modificarPosicion(int posicion, tuplasDPP valor){ // O(1)
            if(heapDeTuplas[posicion] == null){ // O(1)
                heapDeTuplas[posicion] = valor; // O(1)
                tamaño++; // O(1)
            } else {
                heapDeTuplas[posicion] = valor; // O(1)
            }
        }

        private int compararTuplasDPP(tuplasDPP tupla1, tuplasDPP tupla2) { // Comparación entre los votos de Diputados de 2 tuplasDPP  // O(1)
            return Integer.compare(tupla1.obtenerVotosDipu(), tupla2.obtenerVotosDipu());  // O(1)
        }
    }


    // Inicializamos el sistema 
    // Complejidad Temporal : O(P * D)
    public SistemaCNE(String[] nombresDistritos, int[] diputadosPorDistrito, String[] nombresPartidos, int[] ultimasMesasDistritos) {
        distritos = nombresDistritos; // O(1)
        partidos = nombresPartidos; // O(1)
        bancasEnDisputa = diputadosPorDistrito; // O(1)
        mesasDistritos = ultimasMesasDistritos; // O(1)
        votosPresidente = new int[partidos.length]; // O(1)
        votosDiputados = new int[distritos.length][partidos.length]; // O(1)
        bancasPorPartido = new int[distritos.length][partidos.length]; // O(1)
        bancasYaCalculadas = new boolean[distritos.length]; // O(1)
        balotaje = new int[2]; // O(1)
        votosTotalesParaPresidente = 0; // O(1)

        resultadosDeDiputados = new maxHeapTuplas[distritos.length]; // O(1) Esta aparte para diferenciar bien el for y la complejidad.

        tuplasDPP [] tuplearray= new tuplasDPP[partidos.length-1]; // O(1)
        tuplasDPP valorDPP = new tuplasDPP(0,0); // O(1)
        Arrays.fill(tuplearray, valorDPP); // O(P)

        for (int i = 0; i < distritos.length; i++){ // O(D)
            resultadosDeDiputados[i] = new maxHeapTuplas(tuplearray,partidos.length-1); // O(P)
            bancasYaCalculadas[i] = false; // O(1)
        }
    }


    public String nombrePartido(int idPartido) { // Complejidad Temporal : O(1)
        return partidos[idPartido]; //  O(1)
    }


    public String nombreDistrito(int idDistrito) { // Complejidad Temporal : O(1)
        return distritos[idDistrito]; // O(1)
    }


    public int diputadosEnDisputa(int idDistrito) { // Complejidad Temporal : O(1)
        return bancasEnDisputa[idDistrito]; // O(1)
    }


    public String distritoDeMesa(int idMesa) { // Complejidad Temporal : O(log(D))
        BusquedaBinaria busqueda = new BusquedaBinaria(); // O(1)
        int result = busqueda.busquedaBinaria(mesasDistritos, idMesa); // O(log(D)) 
        if(idMesa < mesasDistritos[0]){ // O(1)
            return distritos[0]; // O(1)
        } else {
            return distritos[result]; // O(1)
        }
    }


    public void registrarMesa(int idMesa, VotosPartido[] actaMesa) { // Complejidad Temporal : O(P + log(D))
        BusquedaBinaria busqueda = new BusquedaBinaria(); // O(1)
        int distritoIDMesa = busqueda.busquedaBinaria(mesasDistritos, idMesa); // O(log(D))
        int IDUltimaMesaBuenosAires = mesasDistritos[0]; // O(1)

        for (int i = 0; i < actaMesa.length; i++){ // O(P)
            votosPresidente[i] = votosPresidente[i] + actaMesa[i].presidente; // O(1)
            if(idMesa < IDUltimaMesaBuenosAires){ // O(1)
                votosDiputados[0][i] = votosDiputados[0][i] + actaMesa[i].diputados; // O(1)
            } else {
                votosDiputados[distritoIDMesa][i] = votosDiputados[distritoIDMesa][i] + actaMesa[i].diputados; // O(1)
            }
        }

        tuplasDPP[] nuevo = new tuplasDPP[actaMesa.length-1]; // O(1)

        for (int i = 0; i < (actaMesa.length-1); i++){ // O(P)
            if(idMesa < IDUltimaMesaBuenosAires){ // O(1)
                tuplasDPP tuplaBA = new tuplasDPP(votosDiputados[0][i], i); // O(1)
                nuevo[i] = tuplaBA; // O(1)
            } else {
                tuplasDPP tuplaPARTIDO = new tuplasDPP(votosDiputados[distritoIDMesa][i], i); // O(1)
                nuevo[i] = tuplaPARTIDO; // O(1)
            }
            if (votosPresidente[i] > balotaje[0]){ // O(1)
                balotaje[0] = votosPresidente[i]; // O(1)
            }
        }

        int votosTotalesParaDiputados = sumaTotal(votosDiputados[distritoIDMesa]); // O(P)
        votosTotalesParaPresidente = sumaTotal(votosPresidente); // O(P)

        for (int i = 0; i < (actaMesa.length-1); i++){ // O(P)
            if ((porcentaje(votosDiputados[distritoIDMesa][i],votosTotalesParaDiputados) < 3)){ // O(1)
                tuplasDPP tuplaNoPasaUmbral = new tuplasDPP(0,i); // O(1)
                nuevo[i] = tuplaNoPasaUmbral; // O(1)
            }
            if ((votosPresidente[i] > balotaje[1]) && (votosPresidente[i] < balotaje[0])){ // O(1)
                balotaje[1] = votosPresidente[i]; // O(1)
            }
        }

        maxHeapTuplas calcularHeap = new maxHeapTuplas(nuevo, nuevo.length);  // O(P)
        resultadosDeDiputados[distritoIDMesa] = calcularHeap;  // O(1)
    }

    // Nota acerca de Registrar Mesa:
    // registrarMesa tiene una complejidad de O(P + log(D)) y la justificación es la siguiente, lo primero que hace es buscar el distrito
    // dependiendo la mesa que nos den a registrar, lo hace con busqueda binaria que tiene un costo O(log(D)) ya que busca en mesasDistritos que
    // contiene todos los distritos. Después respecto al resto del código hace 6 cosas especificas en complejidad O(P).
    // 1) Un for que por cada partido asigna sus votos de Presidente y Diputados en VotosPresidente y VotosDiputados.
    // 2) Un for que por cada paritdo crea las Tuplas en base a votosDiputados, que luego se heapificaran y pondran en resultadosDeDiputados.
    // 3) sumaVotosTotalesDiputados calcula el total de votosDiputados, para eso tiene un for que recorre cada partido y va sumando los votos.
    // 4) votosTotalesParaPresidente es una variable donde se guarda el total de votosPresidente, mismo caso que (3).
    // 5) Un for que chequea si cada partido supera el umbral del 3% de votos, en caso contrario asigna un 0 para que al heapificar no le asigne bancas.
    // 6) Por último, calcularHeap que directamente heapifica el array de Tuplas que llenamos en (2) y lo asigna en resultadosDeDiputados

    // Entonces tenemos O(log(D) + P + P + P + P + P + P) ≡ O(log(D) + 6P) ≡ O(log(D) + P)

    // Como cosa importante extra en el ciclo de (2) va guardando en balotaje[0] la cantidad de votos del partido más votado y en el ciclo de (5) 
    // cuando ya fue calculado el máximo y guardado balotaje[0], en base a eso se guarda en balotaje[1] el segundo partido más votado.
    
    // Una última cosa a mencionar es que cada vez que se registra una mesa se repiten todos estos procedimientos y se pisan los valores anteriores.
    // Esto se hace para que cuando se registran varias mesas consecutivamente (tres, cuatro,etc) los valores que queden sean los de la última mesa
    // que se registro. Y todo se hace en base a votosDiputados que es una variable privada del sistema que va sumando por distrito y partido sus votos
    // sin modificar, ni pisar los valores anteriores.

    public float porcentaje(int n, int votosTotales){ // Complejidad Temporal : O(1)
        float porcentaje = 0; // O(1)
        if (votosTotales == 0){ // O(1)
            return 0; // O(1)
        }
        porcentaje = n*100/votosTotales; // O(1)
        return (porcentaje); // O(1)
    }

    public int sumaTotal(int[] votos){ // Complejidad Temporal : O(P)
        int res = 0; // O(1)
        for(int i = 0; i < votos.length; i++){ // O(P)
            res = res + votos[i]; // O(1)
        }
        return res; // O(1)
    }


    public int votosPresidenciales(int idPartido) { // Complejidad Temporal : O(1)
        return votosPresidente[idPartido]; // O(1)
    }


    public int votosDiputados(int idPartido, int idDistrito) { // Complejidad Temporal : O(1)
        return votosDiputados[idDistrito][idPartido]; // O(1)
    }


    // La variable bancasYaCalculadas es un array de boolean con longitud igual a la cantidad de distritos que hay, su función es la siguiente.
    // Al calcular las bancas que se le asignaron a cada partido en un distrito dado, el heap de resultadosDeDiputados en ese distrito se estropea/destruye.
    // porque queda con todas las divisiones de los cocientes de d'Hondt aplicados. Pero lo bueno es que con solo esa iteración ya todas las
    // bancasPorPartido fueron asignadas! Por lo tanto no es necesario re-calcularlas (para el mismo distrito) cada vez que se llame a esta función.
    // Por lo tanto al calcularse por primera vez para un DistritoDado , se asigna un true en bancasYaCalculadas[DistritoDado].
    // Así cuando se vuelva a llamar a esta función para ese DistritoDado pero para consultar las bancas de otro partido, como las bancasPorPartido
    // ya se encuentran calculadas, directamente se puede devolver el array con la asignación de bancas por eso la presencia de ese if.

    public int[] resultadosDiputados(int idDistrito){ // Complejidad Temporal : O(Dd * log(P))
        if (bancasYaCalculadas[idDistrito] == false){ // O(1)
            for(int i = 0; i < bancasEnDisputa[idDistrito]; i++){ // O(Dd)
                int idPartidoConMasVotos = resultadosDeDiputados[idDistrito].mirarElMax().idPartido;  // O(1)
                int votosORIGINALESPartidoConMasVotos = votosDiputados[idDistrito][idPartidoConMasVotos];  // O(1)
                bancasPorPartido[idDistrito][idPartidoConMasVotos] =  bancasPorPartido[idDistrito][idPartidoConMasVotos] + 1;  // O(1)
                int bancasDelPartidoConMasVotos = bancasPorPartido[idDistrito][idPartidoConMasVotos];  // O(1)
                tuplasDPP tuplaMaxModificada = new tuplasDPP(votosORIGINALESPartidoConMasVotos/(bancasDelPartidoConMasVotos+1),idPartidoConMasVotos);  // O(1)
                resultadosDeDiputados[idDistrito].modificarPosicion(0,tuplaMaxModificada);  // O(1)
                resultadosDeDiputados[idDistrito].heapifyDown(0);  // O(log(P))
                bancasYaCalculadas[idDistrito] = true; // O(1)
            }
            return bancasPorPartido[idDistrito]; // O(1)
        } else {
            return bancasPorPartido[idDistrito]; // O(1)
        }
    }


    public boolean hayBallotage(){ // Complejidad Temporal : O(1)
        boolean res = true; // O(1)
        float porcentajeVotosDelPartidoMasVotado = porcentaje(balotaje[0],votosTotalesParaPresidente); // O(1)
        float porcentajeVotosDelSegundoPartidoMasVotado = porcentaje(balotaje[1],votosTotalesParaPresidente); // O(1)
        if (porcentajeVotosDelPartidoMasVotado >= 45){ // O(1)
            res = false; // O(1)
        } else if ((porcentajeVotosDelPartidoMasVotado >= 40) && ((porcentajeVotosDelPartidoMasVotado - porcentajeVotosDelSegundoPartidoMasVotado) > 10)){ // O(1)
            res = false; // O(1)
        }
        return res; // O(1)
    }



    class BusquedaBinaria { // Complejidad Temporal : O(log(N)) donde N es el número de elementos que tiene el array.
        int busquedaBinaria(int Array[], int x) {
            int low = 0;
            int high = Array.length - 1;
      
            while (low <= high){
                int mid = (low + high) / 2;
                int midEnElArray = Array[mid];
          
                if (x == midEnElArray){
                    return (mid+1);
                }
                if (x < midEnElArray){
                    high = mid - 1;
                }
                if (x > midEnElArray){
                    low = mid + 1;
                }
            }
            return (high+1);
        }
    }
}