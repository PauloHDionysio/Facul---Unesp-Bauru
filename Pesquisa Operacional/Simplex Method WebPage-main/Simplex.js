
let flagScroll=0;
function pageScroll() {
    window.scrollBy(0,-4);
    flagScroll++;
    if(flagScroll<20) scrolldelay = setTimeout(pageScroll, 5);
    return;
}



// 1. MUDANÇA NO NÚMERO DE VARIÁVEIS =======================================================================================
var numRestr=2;
var numVariaveis=2;
let matrizPadrao = [];
let matrizOperacao = [];
let vetorBase = [];


document.getElementById('numVariaveis').addEventListener('change', atualizaCampos);
atualizaCampos();



function atualizaCampos(){
    document.getElementById('funcaoObjetivo').innerHTML = ''; //Limpeza dos campos a cada alteração
    document.getElementById('restricoes').innerHTML = '';

    numRestr=0;

    adicionaObjetivo();
    adicionaRestricao();
    adicionaRestricao();
}


// 2. FUNÇÕES DE DINAMICIDADE =========================================================================================

function adicionaObjetivo(){
    numVariaveis = parseInt(document.getElementById('numVariaveis').value) || 2;

    // I. Minimizar ou Maximizar 
        const minMax = document.createElement('select');
        minMax.className = 'minMax';
        minMax.id = 'minMax';
        const opcs = ['Min.', 'Max.'];

        for(let k = 0; k < 2; k++){
            const opc = document.createElement('option');
            opc.value = opcs[k];
            opc.textContent = opcs[k];
            minMax.appendChild(opc);
            minMax.append('   ');
        }
        document.getElementById('funcaoObjetivo').appendChild(minMax);


    // II. Coeficientes, Variáveis e Resultado
        for(let i = 1; i <= numVariaveis; i++){
            const input = document.createElement('input');
            input.id = 'funcObj' + i;
            input.type = 'number';
            input.className = 'coeficiente';
            input.placeholder = `coef X${i}`;
            input.required = true;
            document.getElementById('funcaoObjetivo').appendChild(input);

            if(i < numVariaveis){
                const span = document.createElement('span');
                span.textContent = 'x' + i + '  +  ';
                document.getElementById('funcaoObjetivo').appendChild(span);
            }
        }
}

function removeRestricao(){
    if(numRestr>2){
        const lastAddedDiv = document.getElementById('restricoes').lastElementChild;
        if(lastAddedDiv){
            lastAddedDiv.remove();
            numRestr--;
        }
    }
}

function adicionaRestricao(){
    if(numRestr<5){
        const numVariaveis = parseInt(document.getElementById('numVariaveis').value) || 2;
        const DivRestricao = document.createElement("div");
        
    
        // I. Coeficientes e Variáveis
            for(let i = 1; i <= numVariaveis; i++){
                const input = document.createElement('input');
                input.id = 'restrVar' + i + (numRestr+1); //i=coluna (xi), countRestr=linha
                input.type = 'number';
                input.className = 'coeficiente';
                input.placeholder = `coef X${i}`;
                input.required = true;
                DivRestricao.appendChild(input);
    
                if (i < numVariaveis){
                    const span = document.createElement('span');
                    span.textContent = 'x' + i + ' + ';
                    DivRestricao.appendChild(span);
                }
    
                else if(i==numVariaveis){
                    const span = document.createElement('span');
                    span.textContent = 'x' + i + ' ';
                    DivRestricao.appendChild(span);
                }
            }
    
    
        // II. Seleção do tipo de equação
            const select = document.createElement('select');
            select.className = 'sinalEq';
            select.id = 'sinal' + (numRestr+1);
            const options = ['=', '≤', '≥'];
    
            for(let k = 0; k < options.length; k++){
                const option = document.createElement('option');
                option.value = options[k];
                option.textContent = options[k];
                select.appendChild(option);
                select.append(' ');
            }
            DivRestricao.appendChild(select);
    
    
        // III. Resultado
            const inputResultado = document.createElement('input');
            inputResultado.id = 'restrResult' + (numRestr+1);
            inputResultado.type = 'number';
            inputResultado.className = 'resultado';
            inputResultado.placeholder = 'Resultado';
            inputResultado.required = true;
            DivRestricao.appendChild(inputResultado);
    
    
        document.getElementById("restricoes").appendChild(DivRestricao);
        numRestr++;
    }
}



// 3. FUNÇÕES PARA SALVAR VALORES =========================================================================================

const vetorObjetivo = []; //Bool Min/Max - Coef. Variaveis - Resultado
let matrizRestricao =[]; //Coef. Variaveis - Resultado - Sinal (*numRestrições)


function validaCampos() {
    event.preventDefault();

    const numVariaveis = parseInt(document.getElementById('numVariaveis').value);
    if (isNaN(numVariaveis) || numVariaveis < 2 || numVariaveis > 5) {
        alert('Número de variáveis deve ser um valor entre 2 e 5.');
        return false;
    }

    // Verifique se todos os campos da função objetivo estão preenchidos
    for (let i = 1; i <= numVariaveis; i++) {
        const input = document.getElementById('funcObj' + i);
        if (!input.value) {
            alert('Preencha todos os campos da função objetivo.');
            return false;
        }
    }

    // Verifique se todos os campos das restrições estão preenchidos
    for (let i = 1; i <= numVariaveis; i++) {
        for (let j = 1; j <= numRestr; j++) {
            const input = document.getElementById('restrVar' + i + j);
            if (!input.value) {
                alert('Preencha todos os campos das restrições.');
                return false;
            }
        }
    }

    // Verifique se todos os campos dos resultados das restrições estão preenchidos
    for (let i = 1; i <= numRestr; i++) {
        const inputResultado = document.getElementById('restrResult' + i);
        if (!inputResultado.value) {
            alert('Preencha todos os campos dos resultados das restrições.');
            return false;
        }
    }

    // Se todos os campos estiverem preenchidos, chame a função salvaValor
    salvaValor();
    return false;
}



function salvaValor(){
    //3.1 - FUNÇÃO OBJETIVO ---------------------------------------------------------------
    const numVariaveis = parseInt(document.getElementById('numVariaveis').value);
    
    //I. Maximizar ou Minimizar
    if(document.getElementById('minMax').value === "Min.")
        vetorObjetivo.push(0); //0 para minimizar
    else
        vetorObjetivo.push(1); //1 para maximizar
    

    //II. Coeficientes Objetivo
    for(let i = 1; i <= numVariaveis; i++){
        let valor = parseInt(document.getElementById('funcObj'+i).value);
        vetorObjetivo.push(valor);
    }



    //3.2 - RESTRIÇÕES --------------------------------------------------------------------
    for(let i=0; i<numRestr; i++){ //Matriz Restrição
        matrizRestricao[i]=new Array(numVariaveis+2);
    }

    for(let i = 1; i <=numRestr; i++){ //Colunas Coeficientes
        for(let j=1; j<=numVariaveis; j++){
            let valor = parseInt(document.getElementById('restrVar'+j+i).value);
            matrizRestricao[i-1][j-1]=valor;
        }
    }

    for(let i=1; i<=numRestr; i++){ //Colunas Resultados
        let valor = parseInt(document.getElementById('restrResult'+i).value);
        matrizRestricao[i-1][numVariaveis]=valor;

        var sinal; //Coluna Sinal
        if(document.getElementById('sinal'+i).value === "=")
            sinal=0;
        else if(document.getElementById('sinal'+i).value === "≥")
            sinal=1;
        else
            sinal=-1;
    
        matrizRestricao[i-1][numVariaveis+1]=sinal;
    }

    criaMatrizFormaPadrao();
    console.log("\nCalculando simplex...")
    let resultadoSimplex=0;
    let count=0;
    while(resultadoSimplex===0 && count <20){
        count++;

        if(count===21) console.log("Simplex impossível (sem solução)");

        else{
            resultadoSimplex=pivotamento();
            console.log("Simplex - Iteracao " + count);
            for(let linha=0; linha<numRestr+2; linha++){
                var array=[];
                for(let coluna=0; coluna<numVariaveis+(numRestr*2)+2; coluna++){
                    array[coluna]=matrizOperacao[linha][coluna];
                }
                var str=array.join(' ');
                console.log(str);
            }
            console.log("\n");
        }
    }

    let resultado = matrizPadrao[numRestr+1][numVariaveis+(2*numRestr)+1];
    const divResultado = document.createElement("div");
    const span = document.createElement('h2');
    const botao = document.createElement('button');

    if(resultadoSimplex===-1){
        console.log("Erro de Simplex");
        span.textContent = "Erro de Simplex";
        divResultado.appendChild(span);
    }
    else if(resultadoSimplex===2){
        console.log("Simplex impossível (sem solução)");
        span.textContent = "Simplex impossível (sem solução)";
        divResultado.appendChild(span);
    }
    else if(resultadoSimplex===3){
        console.log("Solução ilimitada/infinita");
        span.textContent = "Solução ilimitada/infinita";
        divResultado.appendChild(span);
    }
    else if(resultadoSimplex===4){
        console.log("Múltiplas soluções");
        span.textContent = "Múltiplas soluções";
        divResultado.appendChild(span);

        const valorZ = document.createElement('p');
        valorZ.textContent = "Z = " + resultado.toFixed(4);
        divResultado.appendChild(valorZ);
    }
    else if(resultadoSimplex===1){
        console.log("Simplex com solução unica!");
        imprimeSimplex();
    }

    document.getElementById("resultadoSimplex").appendChild(divResultado);

    botao.className = "botaoRefresh";
    botao.append("Novo Simplex");
    botao.setAttribute("onclick","refreshPage()");
    document.getElementById("resultadoSimplex").appendChild(botao);

    document.getElementById("resultadoSimplex").hidden=false;

    pageScroll();
    flagScroll=0;
}



//4. FORMA PADRÃO ========================================================================================================================

function criaMatrizFormaPadrao(){
    //I. Preenchimento da matriz padrão
    for(let linha=0; linha<numRestr+2; linha++){ //num linhas -> num restrição + func. obj + CRs
        matrizPadrao[linha]=new Array(numVariaveis+(2*numRestr)+2); //num colunas -> bases + num variaveis + variaveis auxiliares + resultado
    }
    
    for(let linha=0; linha<numRestr+2; linha++){
        for(let coluna=0; coluna<numVariaveis+(numRestr*2)+2; coluna++){
            matrizPadrao[linha][coluna]=0;
        }
    }
    //Linha 0 - Função Objetivo
    for(let coluna=1; coluna<=numVariaveis; coluna++){ //Variáveis normais
        if(vetorObjetivo[0]===1)
            matrizPadrao[0][coluna]=vetorObjetivo[coluna]*-1;
        else
            matrizPadrao[0][coluna]=vetorObjetivo[coluna];
    }

    let restricao=0;
    for(let coluna=numVariaveis+1; coluna<numVariaveis+(numRestr*2)+1; coluna++){ //Variáveis de ajuste
        if(matrizRestricao[restricao][numVariaveis+1]===-1){ //Se a restrição for <=
            matrizPadrao[0][coluna]=0;
            coluna++;
            matrizPadrao[0][coluna]=0;
        }
        else if(matrizRestricao[restricao][numVariaveis+1]===0 || matrizRestricao[restricao][numVariaveis+1]===1){ //Se a restrição for === ou >=
            matrizPadrao[0][coluna]=0;
            coluna++;
            matrizPadrao[0][coluna]=10000;
        }
        restricao++;
    }
    

    //Linha 2 até i-1 - Restrições
    for(let linha=1; linha<numRestr+1; linha++){
        for(let coluna=0; coluna<numVariaveis+(numRestr*2)+1; coluna++){
            if(coluna==0){ //Coluna 0 - Valores das bases na f.obj.
                if(matrizRestricao[linha-1][numVariaveis+1]==-1){ //Se a restrição for <=
                    matrizPadrao[linha][0]=matrizPadrao[0][numVariaveis+2*linha-1];
                    vetorBase[linha]=numVariaveis+2*linha-1;
                }
                else matrizPadrao[linha][0]=matrizPadrao[0][numVariaveis+2*linha];
            }

            else if(coluna==numVariaveis+2*linha-1 || coluna==numVariaveis+2*linha){ //Colunas var. aux. 
                if(matrizRestricao[linha-1][numVariaveis+1]==-1){
                    matrizPadrao[linha][numVariaveis+2*linha-1]=+1;
                    matrizPadrao[linha][numVariaveis+2*linha]=0;
                }
                else if(matrizRestricao[linha-1][numVariaveis+1]==0){
                    matrizPadrao[linha][numVariaveis+2*linha-1]=0;
                    matrizPadrao[linha][numVariaveis+2*linha]=+1;
                }
                else{
                    matrizPadrao[linha][numVariaveis+2*linha-1]=-1;
                    matrizPadrao[linha][numVariaveis+2*linha]=+1;
                }
            }

            else if(coluna>0 && coluna<=numVariaveis){ //Colunas var. normais
                matrizPadrao[linha][coluna]=matrizRestricao[linha-1][coluna-1];
            }
        }
    }

    //III. Coluna Resultado
    for(let i=0; i<numRestr; i++){
        matrizPadrao[i+1][numVariaveis+(2*numRestr)+1]=matrizRestricao[i][numVariaveis];
    }

    //IV. Linha Custo Reduzido (CR)
    for(let coluna=1; coluna<numVariaveis+(numRestr*2)+1; coluna++){
        let CRColuna=matrizPadrao[0][coluna];
        for(let i=1; i<numRestr+1; i++){
            CRColuna-=(matrizPadrao[i][coluna]*matrizPadrao[i][0]);
        }
        matrizPadrao[numRestr+1][coluna]=CRColuna;
    }

    //Imprime matriz simplex
    console.log("Matriz antes do simplex:")
    for(let linha=0; linha<numRestr+2; linha++){
        var array=[];
        for(let coluna=0; coluna<numVariaveis+(numRestr*2)+2; coluna++){
            array[coluna]=matrizPadrao[linha][coluna];
        }
        var str=array.join(' ');
        console.log(str);
    }

    //Cria matriz de operação (espelho da padrão)
    for(let linha=0; linha<numRestr+2; linha++){ //num linhas -> num restrição + func. obj + CRs
        matrizOperacao[linha]=new Array(numVariaveis+(2*numRestr)+2); //num colunas -> bases + num variaveis + variaveis auxiliares + resultado
    }
    
    for(let linha=0; linha<numRestr+2; linha++){
        for(let coluna=0; coluna<numVariaveis+(numRestr*2)+2; coluna++){
            matrizOperacao[linha][coluna]=matrizPadrao[linha][coluna];
        }
    }
}


//5. SIMPLEX ========================================================================================================================

//I. Pivotamento
function pivotamento(){
    /* Possíveis casos:
        Return -1 | ERRO
        Return 0 | Simplex não terminou
        Return 1 | Solução única encontrada
        Return 2 | Não existe solução
        Return 3 | Solução ilimitada/infinita
        Return 4 | Múltiplas soluções
    */

    let colunaResultado;
    let menorNegativo;
    let flagPositivo=0;
    let flagExcesso=0;
    let pivo=0;
    let colunaPivo = 1;
    let linhaPivo = 1;


     //Verifica o menor valor negativo da linha CUSTO REDUZIDO
    menorNegativo=matrizPadrao[numRestr+1][1]
    for(let j=2; j<numVariaveis+(numRestr*2)+1; j++){
        if(matrizPadrao[numRestr+1][j]<menorNegativo){
            menorNegativo = matrizPadrao[numRestr+1][j];
            colunaPivo = j;
        }
    }
    console.log("\nColuna Pivo = " + colunaPivo);

    //Verifica se ainda há variável de excesso na base
    for(let i=1; i<numRestr+1; i++){
        if(matrizPadrao[i][0]===10000) flagExcesso=1;
    }

    //Se os CRs forem maior ou igual a zero (condição de parada)
    if(menorNegativo>0){
        return 1; //CASO 1: SOLUÇÃO ÚNICA
    }

    //Divide o valor da coluna [resultado] pelo valor da coluna [menorNegativo] - para achar o pivo
    colunaResultado=numVariaveis+(2*numRestr)+1;
    let menorPivo=99999999;
    for(let i=1; i<numRestr+1; i++){
        if(matrizPadrao[i][colunaPivo]!==0){
            if((matrizPadrao[i][colunaResultado]/matrizPadrao[i][colunaPivo])>=0){
                if(menorPivo>matrizPadrao[i][colunaResultado]/matrizPadrao[i][colunaPivo]){
                    menorPivo = matrizPadrao[i][colunaResultado]/matrizPadrao[i][colunaPivo];
                    pivo = matrizPadrao[i][colunaPivo];
                    linhaPivo = i;
                }
                flagPositivo=1;
            }
        }
    }
    console.log("Linha pivo = " + linhaPivo);
    console.log("Valor do pivo = " + pivo + "\n");

    if(flagPositivo===0){ //Se todas as colunas resultarem em uma divisão negativa
        return 3; //CASO 3: SOLUÇÃO ILIMITADA
    }
    

    //Pivotamento
    for(let i = 1; i<numRestr+1; i++){
        for(let j = 1; j <numVariaveis+(numRestr*2)+2; j++){
            if(linhaPivo === i){
                matrizOperacao[i][j] = matrizPadrao[i][j] / pivo;
            }
            if(linhaPivo !== i){
                matrizOperacao[i][j] -=  ((matrizPadrao[i][colunaPivo]/pivo) * matrizPadrao[linhaPivo][j]);
            }
        }
    }
    
    //Mudança de base
    matrizOperacao[linhaPivo][0] = matrizOperacao[0][colunaPivo];
    vetorBase[linhaPivo]=colunaPivo;

    //Calcula os novos CRs
    for(let coluna=1; coluna<numVariaveis+(numRestr*2)+1; coluna++){
        let CRColuna=matrizOperacao[0][coluna];
        for(let i=1; i<numRestr+1; i++){
            CRColuna-=(matrizOperacao[i][coluna]*matrizOperacao[i][0]);
        }
        matrizOperacao[numRestr+1][coluna]=CRColuna;
    }

    //Calcula o resultado (z)
    let z=0;
    for(let i = 1; i < numRestr+1; i++){
        z += matrizOperacao[i][0] * matrizOperacao[i][colunaResultado];
    }
    matrizOperacao[numRestr+1][numVariaveis+(numRestr*2)+1]=z;

    //Atualiza a matriz base (matriz padrão)
    for(let linha=0; linha<numRestr+2; linha++){
        for(let coluna=0; coluna<numVariaveis+(numRestr*2)+2; coluna++){
            matrizPadrao[linha][coluna]=matrizOperacao[linha][coluna];
        }
    }

    //Verifica o menor valor negativo da linha CUSTO REDUZIDO
    menorNegativo=matrizPadrao[numRestr+1][1]
    for(let j=2; j<numVariaveis+(numRestr*2)+1; j++){
        if(matrizPadrao[numRestr+1][j]<menorNegativo){
            menorNegativo = matrizPadrao[numRestr+1][j];
            colunaPivo = j;
        }
    }

    //Verifica se ainda há variável de excesso na base
    for(let i=1; i<numRestr+1; i++){
        if(matrizPadrao[i][0]===10000) flagExcesso=1;
    }

    //Se os CRs forem maior ou igual a zero (condição de parada)
    if(menorNegativo>=0){
        if(flagExcesso===1) return 2; //CASO 2: SEM SOLUÇÃO
        return 1; //CASO 1: SOLUÇÃO ÚNICA
    }


    return 0; //CASO 0: O SIMPLEX NÃO TERMINOU
}


//6. IMPRESSÃO DO SIMPLEX ======================================================================================================================

function imprimeSimplex(){
    const divResultado = document.createElement("div");
    let flagBase;

    let resultado = matrizPadrao[numRestr+1][numVariaveis+(2*numRestr)+1]
    if(vetorObjetivo[0]===1) resultado*=-1; //Se a função for para max. -z=-resultado

    //I. Resultado (Z)
    console.log("\nResultado: z = " + resultado);

    const span = document.createElement('h2');
    span.textContent = "Solução Única";
    divResultado.appendChild(span);

    const valorZ = document.createElement('p');
    valorZ.textContent = "Z = " + resultado.toFixed(4);
    divResultado.appendChild(valorZ);

    //II. Variaveis
    console.log("Variaveis:");

    //Verifica se a variável está na base
    for(let i=1; i<=numVariaveis; i++){
        const varFinal = document.createElement('p');
        varFinal.className = "variavelFinal"
        flagBase=0;
        
        for(let j=0; j<=numRestr; j++){
            if(vetorBase[j]===i){
                flagBase=1;
                if(j===0){
                    console.log("X" + i + " = " + (matrizPadrao[1][numVariaveis+(2*numRestr)+1]).toFixed(4));
                    varFinal.textContent = "X" + i + " = " + (matrizPadrao[1][numVariaveis+(2*numRestr)+1]).toFixed(4);
                    divResultado.appendChild(varFinal);
                }
                else{
                    console.log("X" + i + " = " + (matrizPadrao[j][numVariaveis+(2*numRestr)+1]).toFixed(4));
                    varFinal.textContent = "X" + i + " = " + (matrizPadrao[j][numVariaveis+(2*numRestr)+1]).toFixed(4);
                    divResultado.appendChild(varFinal);
                }

            }
        }

        if(flagBase===0){
            console.log("X" + i + " = 0");
            varFinal.textContent = "X" + i + " = " + 0;
            divResultado.appendChild(varFinal);
        }
    }

    document.getElementById("resultadoSimplex").appendChild(divResultado);
    document.getElementById("resultadoSimplex").hidden=false;
   
}


function refreshPage(){
    numRestr=2;
    numVariaveis=2;
    matrizPadrao.length=0;
    matrizOperacao.length=0;
    vetorBase.length=0;
    vetorObjetivo.length=0; //Bool Min/Max - Coef. Variaveis - Resultado
    matrizRestricao.length=0; //Coef. Variaveis - Resultado - Sinal (*numRestrições)
    console.clear();
    window.location.reload();
} 