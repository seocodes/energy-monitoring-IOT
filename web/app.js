// Configuração do Firebase
const firebaseConfig = {
    apiKey: "AIzaSyD36ECWmYCzAT0gut4v0o3XLmykE7oZTj0",
    authDomain: "monitoramente-de-energia---iot.firebaseapp.com",
    databaseURL: "https://monitoramente-de-energia---iot-default-rtdb.firebaseio.com/",
    projectId: "monitoramente-de-energia---iot"
};

// Inicializar Firebase
firebase.initializeApp(firebaseConfig);
const database = firebase.database();
const auth = firebase.auth();

// Credenciais
const email = "azanettev2@gmail.com";
const password = "galinha";

// Função para atualizar os dados na tela
function atualizarDados(dados) {
    // Elementos da interface
    const tensaoElemento = document.getElementById('tension');
    const correnteElemento = document.getElementById('current');
    const statusElemento = document.getElementById('status');

    // Atualizar valores
    if (dados.Tension) {
        tensaoElemento.textContent = dados.Tension.toFixed(2);
    } else {
        tensaoElemento.textContent = '--';
    }

    if (dados.Current) {
        correnteElemento.textContent = dados.Current.toFixed(2);
    } else {
        correnteElemento.textContent = '--';
    }

    // Atualizar status
    statusElemento.textContent = 'Conectado e recebendo dados';
    statusElemento.className = 'status connected';
}

// Função para tratar erros
function mostrarErro(mensagem) {
    const statusElemento = document.getElementById('status');
    statusElemento.textContent = 'Erro: ' + mensagem;
    statusElemento.className = 'status disconnected';
}

// Função para iniciar monitoramento dos dados
function iniciarMonitoramento() {
    const sensorRef = database.ref('Sensor');

    // Monitorar mudanças nos dados
    sensorRef.on('value', function(snapshot) {
        const dados = snapshot.val();
        if (dados) {
            atualizarDados(dados);
        }
    }, function(erro) {
        console.error('Erro ao ler dados:', erro);
        mostrarErro(erro.message);
    });

    // Monitorar estado da conexão
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

// Fazer login e iniciar aplicação
auth.signInWithEmailAndPassword(email, password).then(function() {
    console.log('Login realizado com sucesso');
    iniciarMonitoramento();
}).catch(function(erro) {
    console.error('Erro no login:', erro);
    mostrarErro(erro.message);
});