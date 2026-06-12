.extern isr_handler
.global populate_isr_table

isr0:
    cli
    pushq $0
    pushq $0
    jmp isr_common_stub

isr1:
    cli
    pushq $0
    pushq $1
    jmp isr_common_stub

isr2:
    cli
    pushq $0
    pushq $2
    jmp isr_common_stub

isr3:
    cli
    pushq $0
    pushq $3
    jmp isr_common_stub

isr4:
    cli
    pushq $0
    pushq $4
    jmp isr_common_stub

isr5:
    cli
    pushq $0
    pushq $5
    jmp isr_common_stub

isr6:
    cli
    pushq $0
    pushq $6
    jmp isr_common_stub

isr7:
    cli
    pushq $0
    pushq $7
    jmp isr_common_stub

isr8:
    cli
    pushq $8
    jmp isr_common_stub

isr9:
    cli
    pushq $0
    pushq $9
    jmp isr_common_stub

isr10:
    cli
    pushq $10
    jmp isr_common_stub

isr11:
    cli
    pushq $11
    jmp isr_common_stub

isr12:
    cli
    pushq $12
    jmp isr_common_stub

isr13:
    cli
    pushq $13
    jmp isr_common_stub

isr14:
    cli
    pushq $14
    jmp isr_common_stub

isr15:
    cli
    pushq $0
    pushq $15
    jmp isr_common_stub

isr16:
    cli
    pushq $0
    pushq $16
    jmp isr_common_stub

isr17:
    cli
    pushq $17
    jmp isr_common_stub

isr18:
    cli
    pushq $0
    pushq $18
    jmp isr_common_stub

isr19:
    cli
    pushq $0
    pushq $19
    jmp isr_common_stub

isr20:
    cli
    pushq $0
    pushq $20
    jmp isr_common_stub

isr21:
    cli
    pushq $21
    jmp isr_common_stub

isr22:
    cli
    pushq $0
    pushq $22
    jmp isr_common_stub

isr23:
    cli
    pushq $0
    pushq $23
    jmp isr_common_stub

isr24:
    cli
    pushq $0
    pushq $24
    jmp isr_common_stub

isr25:
    cli
    pushq $0
    pushq $25
    jmp isr_common_stub

isr26:
    cli
    pushq $0
    pushq $26
    jmp isr_common_stub

isr27:
    cli
    pushq $0
    pushq $27
    jmp isr_common_stub

isr28:
    cli
    pushq $0
    pushq $28
    jmp isr_common_stub

isr29:
    cli
    pushq $29
    jmp isr_common_stub

isr30:
    cli
    pushq $30
    jmp isr_common_stub

isr31:
    cli
    pushq $0
    pushq $31
    jmp isr_common_stub

isr32:
    cli
    pushq $0
    pushq $32
    jmp isr_common_stub

isr33:
    cli
    pushq $0
    pushq $33
    jmp isr_common_stub

isr34:
    cli
    pushq $0
    pushq $34
    jmp isr_common_stub

isr35:
    cli
    pushq $0
    pushq $35
    jmp isr_common_stub

isr36:
    cli
    pushq $0
    pushq $36
    jmp isr_common_stub

isr37:
    cli
    pushq $0
    pushq $37
    jmp isr_common_stub

isr38:
    cli
    pushq $0
    pushq $38
    jmp isr_common_stub

isr39:
    cli
    pushq $0
    pushq $39
    jmp isr_common_stub

isr40:
    cli
    pushq $0
    pushq $40
    jmp isr_common_stub

isr41:
    cli
    pushq $0
    pushq $41
    jmp isr_common_stub

isr42:
    cli
    pushq $0
    pushq $42
    jmp isr_common_stub

isr43:
    cli
    pushq $0
    pushq $43
    jmp isr_common_stub

isr44:
    cli
    pushq $0
    pushq $44
    jmp isr_common_stub

isr45:
    cli
    pushq $0
    pushq $45
    jmp isr_common_stub

isr46:
    cli
    pushq $0
    pushq $46
    jmp isr_common_stub

isr47:
    cli
    pushq $0
    pushq $47
    jmp isr_common_stub

isr48:
    cli
    pushq $0
    pushq $48
    jmp isr_common_stub

isr49:
    cli
    pushq $0
    pushq $49
    jmp isr_common_stub

isr50:
    cli
    pushq $0
    pushq $50
    jmp isr_common_stub

isr51:
    cli
    pushq $0
    pushq $51
    jmp isr_common_stub

isr52:
    cli
    pushq $0
    pushq $52
    jmp isr_common_stub

isr53:
    cli
    pushq $0
    pushq $53
    jmp isr_common_stub

isr54:
    cli
    pushq $0
    pushq $54
    jmp isr_common_stub

isr55:
    cli
    pushq $0
    pushq $55
    jmp isr_common_stub

isr56:
    cli
    pushq $0
    pushq $56
    jmp isr_common_stub

isr57:
    cli
    pushq $0
    pushq $57
    jmp isr_common_stub

isr58:
    cli
    pushq $0
    pushq $58
    jmp isr_common_stub

isr59:
    cli
    pushq $0
    pushq $59
    jmp isr_common_stub

isr60:
    cli
    pushq $0
    pushq $60
    jmp isr_common_stub

isr61:
    cli
    pushq $0
    pushq $61
    jmp isr_common_stub

isr62:
    cli
    pushq $0
    pushq $62
    jmp isr_common_stub

isr63:
    cli
    pushq $0
    pushq $63
    jmp isr_common_stub

isr64:
    cli
    pushq $0
    pushq $64
    jmp isr_common_stub

isr65:
    cli
    pushq $0
    pushq $65
    jmp isr_common_stub

isr66:
    cli
    pushq $0
    pushq $66
    jmp isr_common_stub

isr67:
    cli
    pushq $0
    pushq $67
    jmp isr_common_stub

isr68:
    cli
    pushq $0
    pushq $68
    jmp isr_common_stub

isr69:
    cli
    pushq $0
    pushq $69
    jmp isr_common_stub

isr70:
    cli
    pushq $0
    pushq $70
    jmp isr_common_stub

isr71:
    cli
    pushq $0
    pushq $71
    jmp isr_common_stub

isr72:
    cli
    pushq $0
    pushq $72
    jmp isr_common_stub

isr73:
    cli
    pushq $0
    pushq $73
    jmp isr_common_stub

isr74:
    cli
    pushq $0
    pushq $74
    jmp isr_common_stub

isr75:
    cli
    pushq $0
    pushq $75
    jmp isr_common_stub

isr76:
    cli
    pushq $0
    pushq $76
    jmp isr_common_stub

isr77:
    cli
    pushq $0
    pushq $77
    jmp isr_common_stub

isr78:
    cli
    pushq $0
    pushq $78
    jmp isr_common_stub

isr79:
    cli
    pushq $0
    pushq $79
    jmp isr_common_stub

isr80:
    cli
    pushq $0
    pushq $80
    jmp isr_common_stub

isr81:
    cli
    pushq $0
    pushq $81
    jmp isr_common_stub

isr82:
    cli
    pushq $0
    pushq $82
    jmp isr_common_stub

isr83:
    cli
    pushq $0
    pushq $83
    jmp isr_common_stub

isr84:
    cli
    pushq $0
    pushq $84
    jmp isr_common_stub

isr85:
    cli
    pushq $0
    pushq $85
    jmp isr_common_stub

isr86:
    cli
    pushq $0
    pushq $86
    jmp isr_common_stub

isr87:
    cli
    pushq $0
    pushq $87
    jmp isr_common_stub

isr88:
    cli
    pushq $0
    pushq $88
    jmp isr_common_stub

isr89:
    cli
    pushq $0
    pushq $89
    jmp isr_common_stub

isr90:
    cli
    pushq $0
    pushq $90
    jmp isr_common_stub

isr91:
    cli
    pushq $0
    pushq $91
    jmp isr_common_stub

isr92:
    cli
    pushq $0
    pushq $92
    jmp isr_common_stub

isr93:
    cli
    pushq $0
    pushq $93
    jmp isr_common_stub

isr94:
    cli
    pushq $0
    pushq $94
    jmp isr_common_stub

isr95:
    cli
    pushq $0
    pushq $95
    jmp isr_common_stub

isr96:
    cli
    pushq $0
    pushq $96
    jmp isr_common_stub

isr97:
    cli
    pushq $0
    pushq $97
    jmp isr_common_stub

isr98:
    cli
    pushq $0
    pushq $98
    jmp isr_common_stub

isr99:
    cli
    pushq $0
    pushq $99
    jmp isr_common_stub

isr100:
    cli
    pushq $0
    pushq $100
    jmp isr_common_stub

isr101:
    cli
    pushq $0
    pushq $101
    jmp isr_common_stub

isr102:
    cli
    pushq $0
    pushq $102
    jmp isr_common_stub

isr103:
    cli
    pushq $0
    pushq $103
    jmp isr_common_stub

isr104:
    cli
    pushq $0
    pushq $104
    jmp isr_common_stub

isr105:
    cli
    pushq $0
    pushq $105
    jmp isr_common_stub

isr106:
    cli
    pushq $0
    pushq $106
    jmp isr_common_stub

isr107:
    cli
    pushq $0
    pushq $107
    jmp isr_common_stub

isr108:
    cli
    pushq $0
    pushq $108
    jmp isr_common_stub

isr109:
    cli
    pushq $0
    pushq $109
    jmp isr_common_stub

isr110:
    cli
    pushq $0
    pushq $110
    jmp isr_common_stub

isr111:
    cli
    pushq $0
    pushq $111
    jmp isr_common_stub

isr112:
    cli
    pushq $0
    pushq $112
    jmp isr_common_stub

isr113:
    cli
    pushq $0
    pushq $113
    jmp isr_common_stub

isr114:
    cli
    pushq $0
    pushq $114
    jmp isr_common_stub

isr115:
    cli
    pushq $0
    pushq $115
    jmp isr_common_stub

isr116:
    cli
    pushq $0
    pushq $116
    jmp isr_common_stub

isr117:
    cli
    pushq $0
    pushq $117
    jmp isr_common_stub

isr118:
    cli
    pushq $0
    pushq $118
    jmp isr_common_stub

isr119:
    cli
    pushq $0
    pushq $119
    jmp isr_common_stub

isr120:
    cli
    pushq $0
    pushq $120
    jmp isr_common_stub

isr121:
    cli
    pushq $0
    pushq $121
    jmp isr_common_stub

isr122:
    cli
    pushq $0
    pushq $122
    jmp isr_common_stub

isr123:
    cli
    pushq $0
    pushq $123
    jmp isr_common_stub

isr124:
    cli
    pushq $0
    pushq $124
    jmp isr_common_stub

isr125:
    cli
    pushq $0
    pushq $125
    jmp isr_common_stub

isr126:
    cli
    pushq $0
    pushq $126
    jmp isr_common_stub

isr127:
    cli
    pushq $0
    pushq $127
    jmp isr_common_stub

isr128:
    cli
    pushq $0
    pushq $128
    jmp isr_common_stub

isr129:
    cli
    pushq $0
    pushq $129
    jmp isr_common_stub

isr130:
    cli
    pushq $0
    pushq $130
    jmp isr_common_stub

isr131:
    cli
    pushq $0
    pushq $131
    jmp isr_common_stub

isr132:
    cli
    pushq $0
    pushq $132
    jmp isr_common_stub

isr133:
    cli
    pushq $0
    pushq $133
    jmp isr_common_stub

isr134:
    cli
    pushq $0
    pushq $134
    jmp isr_common_stub

isr135:
    cli
    pushq $0
    pushq $135
    jmp isr_common_stub

isr136:
    cli
    pushq $0
    pushq $136
    jmp isr_common_stub

isr137:
    cli
    pushq $0
    pushq $137
    jmp isr_common_stub

isr138:
    cli
    pushq $0
    pushq $138
    jmp isr_common_stub

isr139:
    cli
    pushq $0
    pushq $139
    jmp isr_common_stub

isr140:
    cli
    pushq $0
    pushq $140
    jmp isr_common_stub

isr141:
    cli
    pushq $0
    pushq $141
    jmp isr_common_stub

isr142:
    cli
    pushq $0
    pushq $142
    jmp isr_common_stub

isr143:
    cli
    pushq $0
    pushq $143
    jmp isr_common_stub

isr144:
    cli
    pushq $0
    pushq $144
    jmp isr_common_stub

isr145:
    cli
    pushq $0
    pushq $145
    jmp isr_common_stub

isr146:
    cli
    pushq $0
    pushq $146
    jmp isr_common_stub

isr147:
    cli
    pushq $0
    pushq $147
    jmp isr_common_stub

isr148:
    cli
    pushq $0
    pushq $148
    jmp isr_common_stub

isr149:
    cli
    pushq $0
    pushq $149
    jmp isr_common_stub

isr150:
    cli
    pushq $0
    pushq $150
    jmp isr_common_stub

isr151:
    cli
    pushq $0
    pushq $151
    jmp isr_common_stub

isr152:
    cli
    pushq $0
    pushq $152
    jmp isr_common_stub

isr153:
    cli
    pushq $0
    pushq $153
    jmp isr_common_stub

isr154:
    cli
    pushq $0
    pushq $154
    jmp isr_common_stub

isr155:
    cli
    pushq $0
    pushq $155
    jmp isr_common_stub

isr156:
    cli
    pushq $0
    pushq $156
    jmp isr_common_stub

isr157:
    cli
    pushq $0
    pushq $157
    jmp isr_common_stub

isr158:
    cli
    pushq $0
    pushq $158
    jmp isr_common_stub

isr159:
    cli
    pushq $0
    pushq $159
    jmp isr_common_stub

isr160:
    cli
    pushq $0
    pushq $160
    jmp isr_common_stub

isr161:
    cli
    pushq $0
    pushq $161
    jmp isr_common_stub

isr162:
    cli
    pushq $0
    pushq $162
    jmp isr_common_stub

isr163:
    cli
    pushq $0
    pushq $163
    jmp isr_common_stub

isr164:
    cli
    pushq $0
    pushq $164
    jmp isr_common_stub

isr165:
    cli
    pushq $0
    pushq $165
    jmp isr_common_stub

isr166:
    cli
    pushq $0
    pushq $166
    jmp isr_common_stub

isr167:
    cli
    pushq $0
    pushq $167
    jmp isr_common_stub

isr168:
    cli
    pushq $0
    pushq $168
    jmp isr_common_stub

isr169:
    cli
    pushq $0
    pushq $169
    jmp isr_common_stub

isr170:
    cli
    pushq $0
    pushq $170
    jmp isr_common_stub

isr171:
    cli
    pushq $0
    pushq $171
    jmp isr_common_stub

isr172:
    cli
    pushq $0
    pushq $172
    jmp isr_common_stub

isr173:
    cli
    pushq $0
    pushq $173
    jmp isr_common_stub

isr174:
    cli
    pushq $0
    pushq $174
    jmp isr_common_stub

isr175:
    cli
    pushq $0
    pushq $175
    jmp isr_common_stub

isr176:
    cli
    pushq $0
    pushq $176
    jmp isr_common_stub

isr177:
    cli
    pushq $0
    pushq $177
    jmp isr_common_stub

isr178:
    cli
    pushq $0
    pushq $178
    jmp isr_common_stub

isr179:
    cli
    pushq $0
    pushq $179
    jmp isr_common_stub

isr180:
    cli
    pushq $0
    pushq $180
    jmp isr_common_stub

isr181:
    cli
    pushq $0
    pushq $181
    jmp isr_common_stub

isr182:
    cli
    pushq $0
    pushq $182
    jmp isr_common_stub

isr183:
    cli
    pushq $0
    pushq $183
    jmp isr_common_stub

isr184:
    cli
    pushq $0
    pushq $184
    jmp isr_common_stub

isr185:
    cli
    pushq $0
    pushq $185
    jmp isr_common_stub

isr186:
    cli
    pushq $0
    pushq $186
    jmp isr_common_stub

isr187:
    cli
    pushq $0
    pushq $187
    jmp isr_common_stub

isr188:
    cli
    pushq $0
    pushq $188
    jmp isr_common_stub

isr189:
    cli
    pushq $0
    pushq $189
    jmp isr_common_stub

isr190:
    cli
    pushq $0
    pushq $190
    jmp isr_common_stub

isr191:
    cli
    pushq $0
    pushq $191
    jmp isr_common_stub

isr192:
    cli
    pushq $0
    pushq $192
    jmp isr_common_stub

isr193:
    cli
    pushq $0
    pushq $193
    jmp isr_common_stub

isr194:
    cli
    pushq $0
    pushq $194
    jmp isr_common_stub

isr195:
    cli
    pushq $0
    pushq $195
    jmp isr_common_stub

isr196:
    cli
    pushq $0
    pushq $196
    jmp isr_common_stub

isr197:
    cli
    pushq $0
    pushq $197
    jmp isr_common_stub

isr198:
    cli
    pushq $0
    pushq $198
    jmp isr_common_stub

isr199:
    cli
    pushq $0
    pushq $199
    jmp isr_common_stub

isr200:
    cli
    pushq $0
    pushq $200
    jmp isr_common_stub

isr201:
    cli
    pushq $0
    pushq $201
    jmp isr_common_stub

isr202:
    cli
    pushq $0
    pushq $202
    jmp isr_common_stub

isr203:
    cli
    pushq $0
    pushq $203
    jmp isr_common_stub

isr204:
    cli
    pushq $0
    pushq $204
    jmp isr_common_stub

isr205:
    cli
    pushq $0
    pushq $205
    jmp isr_common_stub

isr206:
    cli
    pushq $0
    pushq $206
    jmp isr_common_stub

isr207:
    cli
    pushq $0
    pushq $207
    jmp isr_common_stub

isr208:
    cli
    pushq $0
    pushq $208
    jmp isr_common_stub

isr209:
    cli
    pushq $0
    pushq $209
    jmp isr_common_stub

isr210:
    cli
    pushq $0
    pushq $210
    jmp isr_common_stub

isr211:
    cli
    pushq $0
    pushq $211
    jmp isr_common_stub

isr212:
    cli
    pushq $0
    pushq $212
    jmp isr_common_stub

isr213:
    cli
    pushq $0
    pushq $213
    jmp isr_common_stub

isr214:
    cli
    pushq $0
    pushq $214
    jmp isr_common_stub

isr215:
    cli
    pushq $0
    pushq $215
    jmp isr_common_stub

isr216:
    cli
    pushq $0
    pushq $216
    jmp isr_common_stub

isr217:
    cli
    pushq $0
    pushq $217
    jmp isr_common_stub

isr218:
    cli
    pushq $0
    pushq $218
    jmp isr_common_stub

isr219:
    cli
    pushq $0
    pushq $219
    jmp isr_common_stub

isr220:
    cli
    pushq $0
    pushq $220
    jmp isr_common_stub

isr221:
    cli
    pushq $0
    pushq $221
    jmp isr_common_stub

isr222:
    cli
    pushq $0
    pushq $222
    jmp isr_common_stub

isr223:
    cli
    pushq $0
    pushq $223
    jmp isr_common_stub

isr224:
    cli
    pushq $0
    pushq $224
    jmp isr_common_stub

isr225:
    cli
    pushq $0
    pushq $225
    jmp isr_common_stub

isr226:
    cli
    pushq $0
    pushq $226
    jmp isr_common_stub

isr227:
    cli
    pushq $0
    pushq $227
    jmp isr_common_stub

isr228:
    cli
    pushq $0
    pushq $228
    jmp isr_common_stub

isr229:
    cli
    pushq $0
    pushq $229
    jmp isr_common_stub

isr230:
    cli
    pushq $0
    pushq $230
    jmp isr_common_stub

isr231:
    cli
    pushq $0
    pushq $231
    jmp isr_common_stub

isr232:
    cli
    pushq $0
    pushq $232
    jmp isr_common_stub

isr233:
    cli
    pushq $0
    pushq $233
    jmp isr_common_stub

isr234:
    cli
    pushq $0
    pushq $234
    jmp isr_common_stub

isr235:
    cli
    pushq $0
    pushq $235
    jmp isr_common_stub

isr236:
    cli
    pushq $0
    pushq $236
    jmp isr_common_stub

isr237:
    cli
    pushq $0
    pushq $237
    jmp isr_common_stub

isr238:
    cli
    pushq $0
    pushq $238
    jmp isr_common_stub

isr239:
    cli
    pushq $0
    pushq $239
    jmp isr_common_stub

isr240:
    cli
    pushq $0
    pushq $240
    jmp isr_common_stub

isr241:
    cli
    pushq $0
    pushq $241
    jmp isr_common_stub

isr242:
    cli
    pushq $0
    pushq $242
    jmp isr_common_stub

isr243:
    cli
    pushq $0
    pushq $243
    jmp isr_common_stub

isr244:
    cli
    pushq $0
    pushq $244
    jmp isr_common_stub

isr245:
    cli
    pushq $0
    pushq $245
    jmp isr_common_stub

isr246:
    cli
    pushq $0
    pushq $246
    jmp isr_common_stub

isr247:
    cli
    pushq $0
    pushq $247
    jmp isr_common_stub

isr248:
    cli
    pushq $0
    pushq $248
    jmp isr_common_stub

isr249:
    cli
    pushq $0
    pushq $249
    jmp isr_common_stub

isr250:
    cli
    pushq $0
    pushq $250
    jmp isr_common_stub

isr251:
    cli
    pushq $0
    pushq $251
    jmp isr_common_stub

isr252:
    cli
    pushq $0
    pushq $252
    jmp isr_common_stub

isr253:
    cli
    pushq $0
    pushq $253
    jmp isr_common_stub

isr254:
    cli
    pushq $0
    pushq $254
    jmp isr_common_stub

isr255:
    cli
    pushq $0
    pushq $255
    jmp isr_common_stub

isr_common_stub:
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    mov %rsp, %rdi
    call isr_handler
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
    add $16, %rsp
    iretq

populate_isr_table:
    lea isr0(%rip), %rax
    mov %rax, 0(%rdi)
    lea isr1(%rip), %rax
    mov %rax, 8(%rdi)
    lea isr2(%rip), %rax
    mov %rax, 16(%rdi)
    lea isr3(%rip), %rax
    mov %rax, 24(%rdi)
    lea isr4(%rip), %rax
    mov %rax, 32(%rdi)
    lea isr5(%rip), %rax
    mov %rax, 40(%rdi)
    lea isr6(%rip), %rax
    mov %rax, 48(%rdi)
    lea isr7(%rip), %rax
    mov %rax, 56(%rdi)
    lea isr8(%rip), %rax
    mov %rax, 64(%rdi)
    lea isr9(%rip), %rax
    mov %rax, 72(%rdi)
    lea isr10(%rip), %rax
    mov %rax, 80(%rdi)
    lea isr11(%rip), %rax
    mov %rax, 88(%rdi)
    lea isr12(%rip), %rax
    mov %rax, 96(%rdi)
    lea isr13(%rip), %rax
    mov %rax, 104(%rdi)
    lea isr14(%rip), %rax
    mov %rax, 112(%rdi)
    lea isr15(%rip), %rax
    mov %rax, 120(%rdi)
    lea isr16(%rip), %rax
    mov %rax, 128(%rdi)
    lea isr17(%rip), %rax
    mov %rax, 136(%rdi)
    lea isr18(%rip), %rax
    mov %rax, 144(%rdi)
    lea isr19(%rip), %rax
    mov %rax, 152(%rdi)
    lea isr20(%rip), %rax
    mov %rax, 160(%rdi)
    lea isr21(%rip), %rax
    mov %rax, 168(%rdi)
    lea isr22(%rip), %rax
    mov %rax, 176(%rdi)
    lea isr23(%rip), %rax
    mov %rax, 184(%rdi)
    lea isr24(%rip), %rax
    mov %rax, 192(%rdi)
    lea isr25(%rip), %rax
    mov %rax, 200(%rdi)
    lea isr26(%rip), %rax
    mov %rax, 208(%rdi)
    lea isr27(%rip), %rax
    mov %rax, 216(%rdi)
    lea isr28(%rip), %rax
    mov %rax, 224(%rdi)
    lea isr29(%rip), %rax
    mov %rax, 232(%rdi)
    lea isr30(%rip), %rax
    mov %rax, 240(%rdi)
    lea isr31(%rip), %rax
    mov %rax, 248(%rdi)
    lea isr32(%rip), %rax
    mov %rax, 256(%rdi)
    lea isr33(%rip), %rax
    mov %rax, 264(%rdi)
    lea isr34(%rip), %rax
    mov %rax, 272(%rdi)
    lea isr35(%rip), %rax
    mov %rax, 280(%rdi)
    lea isr36(%rip), %rax
    mov %rax, 288(%rdi)
    lea isr37(%rip), %rax
    mov %rax, 296(%rdi)
    lea isr38(%rip), %rax
    mov %rax, 304(%rdi)
    lea isr39(%rip), %rax
    mov %rax, 312(%rdi)
    lea isr40(%rip), %rax
    mov %rax, 320(%rdi)
    lea isr41(%rip), %rax
    mov %rax, 328(%rdi)
    lea isr42(%rip), %rax
    mov %rax, 336(%rdi)
    lea isr43(%rip), %rax
    mov %rax, 344(%rdi)
    lea isr44(%rip), %rax
    mov %rax, 352(%rdi)
    lea isr45(%rip), %rax
    mov %rax, 360(%rdi)
    lea isr46(%rip), %rax
    mov %rax, 368(%rdi)
    lea isr47(%rip), %rax
    mov %rax, 376(%rdi)
    lea isr48(%rip), %rax
    mov %rax, 384(%rdi)
    lea isr49(%rip), %rax
    mov %rax, 392(%rdi)
    lea isr50(%rip), %rax
    mov %rax, 400(%rdi)
    lea isr51(%rip), %rax
    mov %rax, 408(%rdi)
    lea isr52(%rip), %rax
    mov %rax, 416(%rdi)
    lea isr53(%rip), %rax
    mov %rax, 424(%rdi)
    lea isr54(%rip), %rax
    mov %rax, 432(%rdi)
    lea isr55(%rip), %rax
    mov %rax, 440(%rdi)
    lea isr56(%rip), %rax
    mov %rax, 448(%rdi)
    lea isr57(%rip), %rax
    mov %rax, 456(%rdi)
    lea isr58(%rip), %rax
    mov %rax, 464(%rdi)
    lea isr59(%rip), %rax
    mov %rax, 472(%rdi)
    lea isr60(%rip), %rax
    mov %rax, 480(%rdi)
    lea isr61(%rip), %rax
    mov %rax, 488(%rdi)
    lea isr62(%rip), %rax
    mov %rax, 496(%rdi)
    lea isr63(%rip), %rax
    mov %rax, 504(%rdi)
    lea isr64(%rip), %rax
    mov %rax, 512(%rdi)
    lea isr65(%rip), %rax
    mov %rax, 520(%rdi)
    lea isr66(%rip), %rax
    mov %rax, 528(%rdi)
    lea isr67(%rip), %rax
    mov %rax, 536(%rdi)
    lea isr68(%rip), %rax
    mov %rax, 544(%rdi)
    lea isr69(%rip), %rax
    mov %rax, 552(%rdi)
    lea isr70(%rip), %rax
    mov %rax, 560(%rdi)
    lea isr71(%rip), %rax
    mov %rax, 568(%rdi)
    lea isr72(%rip), %rax
    mov %rax, 576(%rdi)
    lea isr73(%rip), %rax
    mov %rax, 584(%rdi)
    lea isr74(%rip), %rax
    mov %rax, 592(%rdi)
    lea isr75(%rip), %rax
    mov %rax, 600(%rdi)
    lea isr76(%rip), %rax
    mov %rax, 608(%rdi)
    lea isr77(%rip), %rax
    mov %rax, 616(%rdi)
    lea isr78(%rip), %rax
    mov %rax, 624(%rdi)
    lea isr79(%rip), %rax
    mov %rax, 632(%rdi)
    lea isr80(%rip), %rax
    mov %rax, 640(%rdi)
    lea isr81(%rip), %rax
    mov %rax, 648(%rdi)
    lea isr82(%rip), %rax
    mov %rax, 656(%rdi)
    lea isr83(%rip), %rax
    mov %rax, 664(%rdi)
    lea isr84(%rip), %rax
    mov %rax, 672(%rdi)
    lea isr85(%rip), %rax
    mov %rax, 680(%rdi)
    lea isr86(%rip), %rax
    mov %rax, 688(%rdi)
    lea isr87(%rip), %rax
    mov %rax, 696(%rdi)
    lea isr88(%rip), %rax
    mov %rax, 704(%rdi)
    lea isr89(%rip), %rax
    mov %rax, 712(%rdi)
    lea isr90(%rip), %rax
    mov %rax, 720(%rdi)
    lea isr91(%rip), %rax
    mov %rax, 728(%rdi)
    lea isr92(%rip), %rax
    mov %rax, 736(%rdi)
    lea isr93(%rip), %rax
    mov %rax, 744(%rdi)
    lea isr94(%rip), %rax
    mov %rax, 752(%rdi)
    lea isr95(%rip), %rax
    mov %rax, 760(%rdi)
    lea isr96(%rip), %rax
    mov %rax, 768(%rdi)
    lea isr97(%rip), %rax
    mov %rax, 776(%rdi)
    lea isr98(%rip), %rax
    mov %rax, 784(%rdi)
    lea isr99(%rip), %rax
    mov %rax, 792(%rdi)
    lea isr100(%rip), %rax
    mov %rax, 800(%rdi)
    lea isr101(%rip), %rax
    mov %rax, 808(%rdi)
    lea isr102(%rip), %rax
    mov %rax, 816(%rdi)
    lea isr103(%rip), %rax
    mov %rax, 824(%rdi)
    lea isr104(%rip), %rax
    mov %rax, 832(%rdi)
    lea isr105(%rip), %rax
    mov %rax, 840(%rdi)
    lea isr106(%rip), %rax
    mov %rax, 848(%rdi)
    lea isr107(%rip), %rax
    mov %rax, 856(%rdi)
    lea isr108(%rip), %rax
    mov %rax, 864(%rdi)
    lea isr109(%rip), %rax
    mov %rax, 872(%rdi)
    lea isr110(%rip), %rax
    mov %rax, 880(%rdi)
    lea isr111(%rip), %rax
    mov %rax, 888(%rdi)
    lea isr112(%rip), %rax
    mov %rax, 896(%rdi)
    lea isr113(%rip), %rax
    mov %rax, 904(%rdi)
    lea isr114(%rip), %rax
    mov %rax, 912(%rdi)
    lea isr115(%rip), %rax
    mov %rax, 920(%rdi)
    lea isr116(%rip), %rax
    mov %rax, 928(%rdi)
    lea isr117(%rip), %rax
    mov %rax, 936(%rdi)
    lea isr118(%rip), %rax
    mov %rax, 944(%rdi)
    lea isr119(%rip), %rax
    mov %rax, 952(%rdi)
    lea isr120(%rip), %rax
    mov %rax, 960(%rdi)
    lea isr121(%rip), %rax
    mov %rax, 968(%rdi)
    lea isr122(%rip), %rax
    mov %rax, 976(%rdi)
    lea isr123(%rip), %rax
    mov %rax, 984(%rdi)
    lea isr124(%rip), %rax
    mov %rax, 992(%rdi)
    lea isr125(%rip), %rax
    mov %rax, 1000(%rdi)
    lea isr126(%rip), %rax
    mov %rax, 1008(%rdi)
    lea isr127(%rip), %rax
    mov %rax, 1016(%rdi)
    lea isr128(%rip), %rax
    mov %rax, 1024(%rdi)
    lea isr129(%rip), %rax
    mov %rax, 1032(%rdi)
    lea isr130(%rip), %rax
    mov %rax, 1040(%rdi)
    lea isr131(%rip), %rax
    mov %rax, 1048(%rdi)
    lea isr132(%rip), %rax
    mov %rax, 1056(%rdi)
    lea isr133(%rip), %rax
    mov %rax, 1064(%rdi)
    lea isr134(%rip), %rax
    mov %rax, 1072(%rdi)
    lea isr135(%rip), %rax
    mov %rax, 1080(%rdi)
    lea isr136(%rip), %rax
    mov %rax, 1088(%rdi)
    lea isr137(%rip), %rax
    mov %rax, 1096(%rdi)
    lea isr138(%rip), %rax
    mov %rax, 1104(%rdi)
    lea isr139(%rip), %rax
    mov %rax, 1112(%rdi)
    lea isr140(%rip), %rax
    mov %rax, 1120(%rdi)
    lea isr141(%rip), %rax
    mov %rax, 1128(%rdi)
    lea isr142(%rip), %rax
    mov %rax, 1136(%rdi)
    lea isr143(%rip), %rax
    mov %rax, 1144(%rdi)
    lea isr144(%rip), %rax
    mov %rax, 1152(%rdi)
    lea isr145(%rip), %rax
    mov %rax, 1160(%rdi)
    lea isr146(%rip), %rax
    mov %rax, 1168(%rdi)
    lea isr147(%rip), %rax
    mov %rax, 1176(%rdi)
    lea isr148(%rip), %rax
    mov %rax, 1184(%rdi)
    lea isr149(%rip), %rax
    mov %rax, 1192(%rdi)
    lea isr150(%rip), %rax
    mov %rax, 1200(%rdi)
    lea isr151(%rip), %rax
    mov %rax, 1208(%rdi)
    lea isr152(%rip), %rax
    mov %rax, 1216(%rdi)
    lea isr153(%rip), %rax
    mov %rax, 1224(%rdi)
    lea isr154(%rip), %rax
    mov %rax, 1232(%rdi)
    lea isr155(%rip), %rax
    mov %rax, 1240(%rdi)
    lea isr156(%rip), %rax
    mov %rax, 1248(%rdi)
    lea isr157(%rip), %rax
    mov %rax, 1256(%rdi)
    lea isr158(%rip), %rax
    mov %rax, 1264(%rdi)
    lea isr159(%rip), %rax
    mov %rax, 1272(%rdi)
    lea isr160(%rip), %rax
    mov %rax, 1280(%rdi)
    lea isr161(%rip), %rax
    mov %rax, 1288(%rdi)
    lea isr162(%rip), %rax
    mov %rax, 1296(%rdi)
    lea isr163(%rip), %rax
    mov %rax, 1304(%rdi)
    lea isr164(%rip), %rax
    mov %rax, 1312(%rdi)
    lea isr165(%rip), %rax
    mov %rax, 1320(%rdi)
    lea isr166(%rip), %rax
    mov %rax, 1328(%rdi)
    lea isr167(%rip), %rax
    mov %rax, 1336(%rdi)
    lea isr168(%rip), %rax
    mov %rax, 1344(%rdi)
    lea isr169(%rip), %rax
    mov %rax, 1352(%rdi)
    lea isr170(%rip), %rax
    mov %rax, 1360(%rdi)
    lea isr171(%rip), %rax
    mov %rax, 1368(%rdi)
    lea isr172(%rip), %rax
    mov %rax, 1376(%rdi)
    lea isr173(%rip), %rax
    mov %rax, 1384(%rdi)
    lea isr174(%rip), %rax
    mov %rax, 1392(%rdi)
    lea isr175(%rip), %rax
    mov %rax, 1400(%rdi)
    lea isr176(%rip), %rax
    mov %rax, 1408(%rdi)
    lea isr177(%rip), %rax
    mov %rax, 1416(%rdi)
    lea isr178(%rip), %rax
    mov %rax, 1424(%rdi)
    lea isr179(%rip), %rax
    mov %rax, 1432(%rdi)
    lea isr180(%rip), %rax
    mov %rax, 1440(%rdi)
    lea isr181(%rip), %rax
    mov %rax, 1448(%rdi)
    lea isr182(%rip), %rax
    mov %rax, 1456(%rdi)
    lea isr183(%rip), %rax
    mov %rax, 1464(%rdi)
    lea isr184(%rip), %rax
    mov %rax, 1472(%rdi)
    lea isr185(%rip), %rax
    mov %rax, 1480(%rdi)
    lea isr186(%rip), %rax
    mov %rax, 1488(%rdi)
    lea isr187(%rip), %rax
    mov %rax, 1496(%rdi)
    lea isr188(%rip), %rax
    mov %rax, 1504(%rdi)
    lea isr189(%rip), %rax
    mov %rax, 1512(%rdi)
    lea isr190(%rip), %rax
    mov %rax, 1520(%rdi)
    lea isr191(%rip), %rax
    mov %rax, 1528(%rdi)
    lea isr192(%rip), %rax
    mov %rax, 1536(%rdi)
    lea isr193(%rip), %rax
    mov %rax, 1544(%rdi)
    lea isr194(%rip), %rax
    mov %rax, 1552(%rdi)
    lea isr195(%rip), %rax
    mov %rax, 1560(%rdi)
    lea isr196(%rip), %rax
    mov %rax, 1568(%rdi)
    lea isr197(%rip), %rax
    mov %rax, 1576(%rdi)
    lea isr198(%rip), %rax
    mov %rax, 1584(%rdi)
    lea isr199(%rip), %rax
    mov %rax, 1592(%rdi)
    lea isr200(%rip), %rax
    mov %rax, 1600(%rdi)
    lea isr201(%rip), %rax
    mov %rax, 1608(%rdi)
    lea isr202(%rip), %rax
    mov %rax, 1616(%rdi)
    lea isr203(%rip), %rax
    mov %rax, 1624(%rdi)
    lea isr204(%rip), %rax
    mov %rax, 1632(%rdi)
    lea isr205(%rip), %rax
    mov %rax, 1640(%rdi)
    lea isr206(%rip), %rax
    mov %rax, 1648(%rdi)
    lea isr207(%rip), %rax
    mov %rax, 1656(%rdi)
    lea isr208(%rip), %rax
    mov %rax, 1664(%rdi)
    lea isr209(%rip), %rax
    mov %rax, 1672(%rdi)
    lea isr210(%rip), %rax
    mov %rax, 1680(%rdi)
    lea isr211(%rip), %rax
    mov %rax, 1688(%rdi)
    lea isr212(%rip), %rax
    mov %rax, 1696(%rdi)
    lea isr213(%rip), %rax
    mov %rax, 1704(%rdi)
    lea isr214(%rip), %rax
    mov %rax, 1712(%rdi)
    lea isr215(%rip), %rax
    mov %rax, 1720(%rdi)
    lea isr216(%rip), %rax
    mov %rax, 1728(%rdi)
    lea isr217(%rip), %rax
    mov %rax, 1736(%rdi)
    lea isr218(%rip), %rax
    mov %rax, 1744(%rdi)
    lea isr219(%rip), %rax
    mov %rax, 1752(%rdi)
    lea isr220(%rip), %rax
    mov %rax, 1760(%rdi)
    lea isr221(%rip), %rax
    mov %rax, 1768(%rdi)
    lea isr222(%rip), %rax
    mov %rax, 1776(%rdi)
    lea isr223(%rip), %rax
    mov %rax, 1784(%rdi)
    lea isr224(%rip), %rax
    mov %rax, 1792(%rdi)
    lea isr225(%rip), %rax
    mov %rax, 1800(%rdi)
    lea isr226(%rip), %rax
    mov %rax, 1808(%rdi)
    lea isr227(%rip), %rax
    mov %rax, 1816(%rdi)
    lea isr228(%rip), %rax
    mov %rax, 1824(%rdi)
    lea isr229(%rip), %rax
    mov %rax, 1832(%rdi)
    lea isr230(%rip), %rax
    mov %rax, 1840(%rdi)
    lea isr231(%rip), %rax
    mov %rax, 1848(%rdi)
    lea isr232(%rip), %rax
    mov %rax, 1856(%rdi)
    lea isr233(%rip), %rax
    mov %rax, 1864(%rdi)
    lea isr234(%rip), %rax
    mov %rax, 1872(%rdi)
    lea isr235(%rip), %rax
    mov %rax, 1880(%rdi)
    lea isr236(%rip), %rax
    mov %rax, 1888(%rdi)
    lea isr237(%rip), %rax
    mov %rax, 1896(%rdi)
    lea isr238(%rip), %rax
    mov %rax, 1904(%rdi)
    lea isr239(%rip), %rax
    mov %rax, 1912(%rdi)
    lea isr240(%rip), %rax
    mov %rax, 1920(%rdi)
    lea isr241(%rip), %rax
    mov %rax, 1928(%rdi)
    lea isr242(%rip), %rax
    mov %rax, 1936(%rdi)
    lea isr243(%rip), %rax
    mov %rax, 1944(%rdi)
    lea isr244(%rip), %rax
    mov %rax, 1952(%rdi)
    lea isr245(%rip), %rax
    mov %rax, 1960(%rdi)
    lea isr246(%rip), %rax
    mov %rax, 1968(%rdi)
    lea isr247(%rip), %rax
    mov %rax, 1976(%rdi)
    lea isr248(%rip), %rax
    mov %rax, 1984(%rdi)
    lea isr249(%rip), %rax
    mov %rax, 1992(%rdi)
    lea isr250(%rip), %rax
    mov %rax, 2000(%rdi)
    lea isr251(%rip), %rax
    mov %rax, 2008(%rdi)
    lea isr252(%rip), %rax
    mov %rax, 2016(%rdi)
    lea isr253(%rip), %rax
    mov %rax, 2024(%rdi)
    lea isr254(%rip), %rax
    mov %rax, 2032(%rdi)
    lea isr255(%rip), %rax
    mov %rax, 2040(%rdi)
    ret
