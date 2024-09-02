// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
	modules: [
		"@vueuse/nuxt",
		"@nuxtjs/seo",
		"@nuxt/icon",
		"@nuxtjs/tailwindcss",
		"@nuxt/eslint"
	],
	site: {
		name: "Poto",
		url: "https://poto.karsten.zip",
		description: "Poto Image Converter",
		defautlLocale: "en"
	},
	icon: {
		mode: "svg"
	},
	css: ["~/assets/css/transitions.css"],
	typescript: {
		typeCheck: true
	},
	compatibilityDate: "2024-04-03",
	devtools: { enabled: true }
})
