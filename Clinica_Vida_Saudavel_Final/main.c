/*
Utilizar este comando pra compilar:

gcc -Ilib -Ilib_old -I. main.c lib/fila_hospital.c lib/registro_paciente.c lib/escala_medicos.c lib/historico_atendimento.c lib_old/lista_com_cabeca.c -o main
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// As três bibliotecas seguintes foram criadas por nós, a fim de organizar melhor o código
#include "fila_hospital.h"
#include "escala_medicos.h"
#include "historico_atendimento.h"

static void ler_linha(const char *msg, char *dest, int tam) {
    printf("%s", msg);
    if (fgets(dest, tam, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    dest[strcspn(dest, "\r\n")] = '\0';
}

static int ler_int(const char *msg) {
    char buf[32];
    ler_linha(msg, buf, sizeof(buf));
    return atoi(buf);
}

static int ler_tipo() {
    printf("  Tipos: 1 = Normal | 2 = Preferencial | 3 = Emergencial\n");
    return ler_int("  Tipo: ");
}

static const char *nome_tipo(int t) {
    switch (t) {
        case TIPO_NORMAL:       return "Normal";
        case TIPO_PREFERENCIAL: return "Preferencial";
        case TIPO_EMERGENCIAL:  return "Emergencial";
        default:                return "Invalido";
    }
}

static No *achar_no(No *registro, const char *nome) {
    unsigned int id = criar_id(nome);
    for (No *q = registro->prox; q != NULL; q = q->prox)
        if (q->id == id) return q;
    return NULL;
}

// Menu principal
static void menu() {
    printf("\n=========== HOSPITAL ===========\n");
    printf(" 1) Cadastrar paciente no registro\n");
    printf(" 2) Listar registro\n");
    printf(" 3) Buscar paciente no registro\n");
    printf(" 4) Excluir paciente do registro\n");
    printf(" 5) Chamar paciente do registro para a fila\n");
    printf(" 6) Cadastrar e ja colocar na fila\n");
    printf(" 7) Ver fila (ordem de atendimento)\n");
    printf(" 8) Ver proximo da fila\n");
    printf(" 9) Atender proximo\n");
    printf("10) Desfazer ultimo atendimento (voltar para a fila)\n");
    printf("11) Adicionar Medico na Escala de Plantao\n");
    printf("12) Avancar Medico Plantonista\n");
    printf("13) Remover Medico Atual da Escala\n");
    printf("14) Listar Escala de Medicos\n");
    printf("15) Carregar dados de exemplo\n");
    printf("16) Ver historico de atendimentos\n");
    printf(" 0) Sair\n");
}

// Essa função foi criada apenas pra facilitar o exemplo de como o programa funciona
static void carregar_exemplo(No *registro, NoMedico **escala) {
    adicionar_paciente(registro, "Ana",        TIPO_NORMAL);
    adicionar_paciente(registro, "Bruno",      TIPO_EMERGENCIAL);
    adicionar_paciente(registro, "Dona Maria", TIPO_PREFERENCIAL);
    adicionar_paciente(registro, "Carlos",     TIPO_NORMAL);
    adicionar_paciente(registro, "Helena",     TIPO_EMERGENCIAL);
    printf("5 pacientes cadastrados no registro (use a opcao 5 para chama-los para a fila).\n");
    
    // Exemplos de medicos
    escala_inserir(escala, 101);
    escala_inserir(escala, 102);
    escala_inserir(escala, 103);
    printf("3 Medicos adicionados a escala rotativa de plantao (CRMs: 101, 102, 103).\n");
}

int main() {
    No *registro = criar_registro_pacientes();
    FilaHospital *fila = fila_hospital_criar();
    Historico *historico = historico_criar();
    NoMedico *escala_medicos = escala_criar();
    
    char nome[100];
    int op;

    do {
        menu();
        op = ler_int("Escolha: ");
        printf("\n");

        switch (op) {
        case 1: {
            ler_linha("  Nome: ", nome, sizeof(nome));
            if (nome[0] == '\0') { printf("Nome vazio.\n"); break; }
            if (achar_no(registro, nome)) { printf("Ja existe paciente com esse nome (mesmo id).\n"); break; }
            int tipo = ler_tipo();
            if (tipo < TIPO_NORMAL || tipo > TIPO_EMERGENCIAL) { printf("Tipo invalido.\n"); break; }
            adicionar_paciente(registro, nome, tipo);
            printf("%s cadastrado (%s). Id: %u\n", nome, nome_tipo(tipo), criar_id(nome));
            break;
        }

        case 2: {
            printf("--- Registro ---\n");
            imprimir_lista_paciente(registro);
            printf("\n");
            break;
        }

        case 3: {
            ler_linha("  Nome: ", nome, sizeof(nome));
            No *q = achar_no(registro, nome);
            if (q) printf("Encontrado -> Id: %u | Nome: %s | Tipo: %s\n", q->id, q->pessoa.nome, nome_tipo(q->pessoa.tipo));
            else   printf("Paciente nao encontrado no registro.\n");
            break;
        }

        case 4: {
            ler_linha("  Nome: ", nome, sizeof(nome));
            if (!achar_no(registro, nome)) { printf("Paciente nao encontrado no registro.\n"); break; }
            excluir_paciente(registro, criar_id(nome));
            printf("%s removido do registro (se ja estiver na fila, continua nela).\n", nome);
            break;
        }

        case 5: {
            ler_linha("  Nome: ", nome, sizeof(nome));
            if (fila_hospital_contem(fila, criar_id(nome))) { printf("%s ja esta na fila.\n", nome); break; }
            if (fila_hospital_enfileirar_registro(fila, registro, criar_id(nome)))
                printf("%s entrou na fila.\n", nome);
            else
                printf("Nao foi possivel: paciente nao esta no registro.\n");
            break;
        }

        case 6: {
            ler_linha("  Nome: ", nome, sizeof(nome));
            if (nome[0] == '\0') { printf("Nome vazio.\n"); break; }
            if (fila_hospital_contem(fila, criar_id(nome))) { printf("%s ja esta na fila.\n", nome); break; }
            int tipo = ler_tipo();
            if (tipo < TIPO_NORMAL || tipo > TIPO_EMERGENCIAL) { printf("Tipo invalido.\n"); break; }
            if (!achar_no(registro, nome)) adicionar_paciente(registro, nome, tipo);
            fila_hospital_enfileirar(fila, nome, tipo);
            printf("%s cadastrado e colocado na fila (%s).\n", nome, nome_tipo(tipo));
            break;
        }

        case 7: {
            printf("--- Fila (%d esperando) ---\n", fila_hospital_tamanho(fila));
            fila_hospital_imprimir(fila);
            break;
        }

        case 8: {
            paciente p;
            if (fila_hospital_proximo(fila, &p))
                printf("Proximo: %s (%s)\n", p.nome, nome_tipo(p.tipo));
            else
                printf("Fila vazia.\n");
            break;
        }

        case 9: {
            if (escala_medicos == NULL) {
                printf("Atendimento nao realizado: nao ha medicos na escala de plantao no momento.\n");
                break;
            }

            paciente p;
            if (fila_hospital_atender(fila, &p)) {
                int crm = escala_atual(escala_medicos);
                printf("Atendendo: %s (%s) pelo Medico CRM %d. Restam %d na fila.\n", p.nome, nome_tipo(p.tipo), crm, fila_hospital_tamanho(fila));
                
                historico_empilhar(historico, p, crm);
                
                escala_avancar(&escala_medicos);
                printf("Proximo medico da vez: CRM %d.\n", escala_atual(escala_medicos));
            } else {
                printf("Fila vazia, ninguem para atender.\n");
            }
            break;
        }

        case 10: {
            // Aqui se desfaz o ultimo atendimento, ou seja, o paciente sai da pilha e volta pra fila
            paciente p;
            if (historico_topo(historico, &p, NULL) && fila_hospital_contem(fila, criar_id(p.nome))) {
                printf("Nao foi possivel desfazer: %s ja esta na fila novamente.\n", p.nome);
                break;
            }
            if (!historico_desfazer(historico, &p)) {
                printf("O historico de atendimentos esta vazio. Nenhum atendimento para desfazer.\n");
                break;
            }
            fila_hospital_enfileirar(fila, p.nome, p.tipo);
            printf("Atendimento desfeito! %s (%s) retornou a fila.\n", p.nome, nome_tipo(p.tipo));
            break;
        }

        case 11: {
            int crm = ler_int("Digite o CRM do Medico: ");
            if (crm <= 0) { printf("CRM invalido.\n"); break; }
            if (escala_inserir(&escala_medicos, crm))
                printf("Medico CRM %d inserido na escala rotativa.\n", crm);
            else
                printf("Medico CRM %d ja esta na escala.\n", crm);
            break;
        }

        case 12: {
            if (escala_medicos == NULL) {
                printf("A escala de medicos esta vazia.\n");
            } else {
                escala_avancar(&escala_medicos);
                printf("Escala avancada. O medico atual agora e o CRM %d.\n", escala_atual(escala_medicos));
            }
            break;
        }

        case 13: {
            if (escala_medicos == NULL) {
                printf("A escala de medicos ja esta vazia.\n");
            } else {
                int crm_removido = escala_atual(escala_medicos);
                escala_remover_atual(&escala_medicos);
                printf("Medico CRM %d removido da escala de plantao.\n", crm_removido);
            }
            break;
        }

        case 14: {
            printf("--- Escala Rotativa de Medicos (o primeiro e o da vez) ---\n");
            escala_imprimir(escala_medicos);
            break;
        }

        case 15: {
            carregar_exemplo(registro, &escala_medicos);
            break;
        }

        case 16: {
            printf("--- Historico de atendimentos (%d) ---\n", historico_tamanho(historico));
            historico_imprimir(historico);
            break;
        }

        case 0: {
            printf("Processo encerrado\n");
            break;
        }

        default:
            printf("Opcao invalida.\n");
        }

    } while (op != 0);

    historico_destruir(&historico);
    fila_hospital_destruir(&fila);
    escala_destruir(&escala_medicos);
    destruir_lista(&registro);
    return 0;
}