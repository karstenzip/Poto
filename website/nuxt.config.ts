export default defineNuxtConfig({
	modules: [
		"@vueuse/nuxt",
		"@nuxtjs/seo",
		"@nuxtjs/tailwindcss",
		!process.env.DOCKER_BUILD && "@nuxt/eslint"
	],
	site: {
		name: "Poto",
		url: "https://poto.karsten.zip",
		description: "Poto Image Converter",
		defaultLocale: "en"
	},
	css: ["~/assets/css/transitions.css"],
	typescript: {
		typeCheck: true
	},
	compatibilityDate: "2025-07-15",
	devtools: { enabled: true }
})
