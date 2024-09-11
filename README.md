# HackOS

**HackOS** é um sistema operacional minimalista projetado para rodar diretamente de um *stick* USB, focado em segurança e privacidade. Ele opera em modo "stateless", o que significa que nenhum dado é salvo permanentemente no *stick* USB ou em qualquer outro dispositivo após o sistema ser desligado. Todas as operações e arquivos temporários são armazenados na RAM, proporcionando um ambiente seguro e sem persistência de dados.

## Funcionalidades

- **Execução diretamente de um *stick* USB** com suporte a inicialização rápida.
- **Sistema sem persistência de dados**: todos os dados são temporários e armazenados na RAM.
- **Interface de linha de comando simples (CLI)** para interação com o sistema.
- **Gerenciamento básico de processos e tarefas** com um agendador round-robin.
- **Suporte a sistemas de arquivos temporários (`tmpfs`)** para armazenamento em RAM.

## Como Usar

### Passo 1: Compilar o Sistema Operacional

Antes de usar o HackOS, você precisará compilar os arquivos-fonte para criar uma imagem binária que possa ser gravada no *stick* USB.

1. **Clone o repositório** para o seu ambiente de desenvolvimento:
   ```bash
   git clone https://github.com/seu-repositorio/hackos.git
   cd hackos
   ```

2. **Compile o sistema operacional** usando o `Makefile` incluído:
   ```bash
   make
   ```

   Isso irá gerar uma imagem de disco `hackos.img` no diretório de trabalho atual.

### Passo 2: Gravar a Imagem no USB com Balena Etcher

Agora que a imagem `.img` foi gerada, você pode gravá-la no *stick* USB usando o **Balena Etcher**:

1. **Baixe e instale o [Balena Etcher](https://www.balena.io/etcher/)** se ainda não o tiver.
   
2. **Abra o Balena Etcher** e siga os passos abaixo:

   - Clique em "Flash from file" e selecione a imagem `hackos.img` que você compilou.
   - Conecte o *stick* USB ao seu computador.
   - O Etcher deve detectar automaticamente o USB. Selecione o dispositivo correto.
   - Clique em "Flash!" para gravar a imagem no USB.

3. **Espere a gravação terminar** e ejete o *stick* USB.

### Passo 3: Executar o HackOS

1. **Conecte o *stick* USB** ao computador onde deseja rodar o HackOS.
2. **Reinicie o computador** e entre na BIOS/UEFI para configurar o boot a partir do *stick* USB.
3. **Selecione o USB como dispositivo de boot**. O HackOS deve iniciar diretamente na RAM, sem persistir dados em nenhum dispositivo.

### Funcionalidades Avançadas

- **CLI Simples**: Após o boot, você verá uma interface de linha de comando simples, onde poderá usar comandos como `ls`, `echo`, `clear`, entre outros.
- **Sistema Temporário (`tmpfs`)**: Qualquer arquivo que você criar ou modificar durante a sessão será armazenado na RAM e será perdido quando o sistema for desligado.

### Observações

- **Segurança**: Nenhum dado será salvo permanentemente, então o sistema é ideal para situações onde a privacidade é uma preocupação.
- **Portabilidade**: O sistema é leve e pode ser facilmente transportado e executado em diferentes máquinas a partir de um *stick* USB.

---

Obrigado Por Ler :)
