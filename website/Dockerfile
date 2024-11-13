FROM node:20-alpine AS build

WORKDIR /usr/src/app

ENV NODE_ENV=production

COPY package*.json ./

RUN npm ci --omit=dev

COPY . .

RUN npm run build

FROM node:20-alpine AS final

WORKDIR /usr/src/app

ENV NODE_ENV=production

COPY --from=build --chown=node /usr/src/app/node_modules node_modules
COPY --from=build --chown=node /usr/src/app/.output .output

USER node

EXPOSE 3000/tcp

CMD ["node", ".output/server/index.mjs"]
