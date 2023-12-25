function articleValidator(ctx) {
    ctx.validateBody('title')
      .required('文章标题 title不能为空')
      .isString()
      .trim()
    ctx.validateBody('author')
      .required('文章作者 author 不能为空')
      .isString()
      .trim()
    ctx.validateBody('cover')
      .required('文章封面 cover 不能为空')
      .isString()
      .trim()
    ctx.validateBody('keyword')
      .required('文章关键字 keyword不能为空')
      .isString()
      .trim()
    ctx.validateBody('description')
      .required('文章简介 description 不能为空')
      .isString()
      .trim()
    ctx.validateBody('content')
      .required('文章内容 content 不能为空')
      .isString()
      .trim()
    ctx.validateBody('category_id')
      .required('文章分类 category_id 不能为空')
      .isString()
      .trim()
  
  }
  module.exports = {
    articleValidator
  }