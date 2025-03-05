FROM node:22-alpine AS base

WORKDIR /usr/src/app

ENV NODE_ENV=production

FROM base AS builder

COPY package*.json ./
RUN npm ci --omit=dev

COPY . .
RUN npm run build

FROM base AS runner

COPY --from=builder --chown=node /usr/src/app/.output ./

USER node
EXPOSE 3000/tcp

CMD ["node", "server/index.mjs"]
