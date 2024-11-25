
const firebaseConfig = {
    apiKey: "AIzaSyD36ECWmYCzAT0gut4v0o3XLmykE7oZTj0",
    authDomain: "monitoramente-de-energia---iot.firebaseapp.com",
    databaseURL: "https://monitoramente-de-energia---iot-default-rtdb.firebaseio.com/",
    projectId: "monitoramente-de-energia---iot"
};


firebase.initializeApp(firebaseConfig);
const database = firebase.database();
const auth = firebase.auth();


const email = "azanettev2@gmail.com";
const password = "galinha";


function atualizarDados(dados) {
    const tensaoElemento = document.getElementById('tension');
    const correnteElemento = document.getElementById('current');
    const potenciaElemento = document.getElementById('potencia');
    const statusElemento = document.getElementById('status');

    // Atualizar valores
    if (dados.Tensao) {
        tensaoElemento.textContent = dados.Tensao.toFixed(2);
    } else {
        tensaoElemento.textContent = '--';
    }

    if (dados.Corrente) {
        correnteElemento.textContent = dados.Corrente.toFixed(2);
    } else {
        correnteElemento.textContent = '--';
    }

    if (dados.Potencia) {
        potenciaElemento.textContent = dados.Potencia.toFixed(2);
    } else {
        potenciaElemento.textContent = '--';
    }

    statusElemento.textContent = 'Conectado e recebendo dados';
    statusElemento.className = 'status connected';
}

function mostrarErro(mensagem) {
    const statusElemento = document.getElementById('status');
    statusElemento.textContent = 'Erro: ' + mensagem;
    statusElemento.className = 'status disconnected';
}


function iniciarMonitoramento() {
    const sensorRef = database.ref('Sensor');


    sensorRef.on('value', function(snapshot) {
        const dados = snapshot.val();
        if (dados) {
            atualizarDados(dados);
        }
    }, function(erro) {
        console.error('Erro ao ler dados:', erro);
        mostrarErro(erro.message);
    });

    const connectedRef = database.ref('.info/connected');
    connectedRef.on('value', function(snap) {
        const statusElemento = document.getElementById('status');
        if (snap.val() === true) {
            statusElemento.textContent = 'Conectado e recebendo dados';
            statusElemento.className = 'status connected';
        } else {
            statusElemento.textContent = 'Desconectado do servidor';
            statusElemento.className = 'status disconnected';
        }
    });
}

auth.signInWithEmailAndPassword(email, password).then(function() {
    console.log('Login realizado com sucesso');
    iniciarMonitoramento();
}).catch(function(erro) {
    console.error('Erro no login:', erro);
    mostrarErro(erro.message);
});
