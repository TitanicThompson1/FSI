    # Trabalho realizado na Semana #3

## Identificação
- CVE-2017-0144
- Vulnerabilidade do Microsoft Server Message Block 1.0 (SMBv1), devido à maneira como este manipula certas solicitações
- Permite a execução remota de código
- Encontrada em Windows Vista, Windows 7, Windows 8.1, Windows 10, Windows Server 2008, Windows Server 2012, and Windows Server 2016

## Catalogação

 - Descoberta pela NSA alegadamente 5 anos antes de ser tornada pública
 - Foi comunicada à Microsoft após o roubo do roubo da ferramenta EternalBlue que explora a vulnerabilidade
 - A 14-03-2017 a Microsoft publica o boletim de segurança onde divulga a existência da vulnerabilidade
 - Classificado como Crítico(9.2) no indice CVSS

## Exploit

- EternalBlue
    - Foi divulgado pelo grupo Shadow Brokers
    - Funciona através do envio de pacotes modificados para o servidor SMB permitindo a execução de código remotamente
    - Metasploit: use exploit/windows/smb/ms17_010_eternalblue
    - [ExploitDB](https://www.exploit-db.com/exploits/42031)


## Ataques

- **Maio, 2017:** O ataque de Ransomware **WannaCry** abusou da vulnerabilidade **EternalBlue** para se espalhar; 
- **Fevereiro, 2018:** O **Eternal Blue** foi portado para todos os sistemas operativos Windows; 
- **Maio, 2019:** A cidade de Baltimore nos EUA foi vítima de milhares de ataques provocados por este exploit, bloqueando computadores e afetando muitos serviços básicos.
